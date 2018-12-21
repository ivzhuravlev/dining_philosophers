#include "mainwindow.h"
#include "logwidget.h"
#include "dinnerscenemanager.h"
#include "settingsserializer.h"
#include "settingsdialog.h"
#include "dphCore/dinner.h"

#include <QApplication>
#include <QScreen>
#include <QStyle>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QIcon>
#include <QSplitter>
#include <QGraphicsView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	_availGeometry(findAvailableWindowGeometry())
{
	_settingsSerializer = new SettingsSerializer(qApp->organizationName(), qApp->applicationName(), this);

	loadSettings();
	createWidgets();
	createActions();
	createDinner();

	setCentralWidget(_splitter);
	setGeometry(_availGeometry);
	setWindowIcon(QIcon(":/resources/philosophy.png"));
}

void MainWindow::closeEvent(QCloseEvent * override)
{
	saveSettings();
}

void MainWindow::openAbout()
{
	QMessageBox::about(this, tr("About"),
		tr("Simple solution of classic <br>Dining Philosophers problem<br>") +
		QString("<a href=\"https://github.com/ivzhuravlev/dining_philosophers/\">GitHub</a><br>") +
		tr("(c) Ivan Zhuravlev, 2018"));
}

void MainWindow::openAboutQt()
{
	QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::loadSettings()
{
	_dinnerSettings = _settingsSerializer->loadDinnerSettings();
	_sceneSettings = _settingsSerializer->loadSceneSettings();
	_visualSettings = _settingsSerializer->loadVisualSettings();
}

void MainWindow::saveSettings()
{
	_settingsSerializer->saveDinnerSettings(_dinnerSettings);
	_settingsSerializer->saveSceneSettings(_sceneSettings);
	_settingsSerializer->saveVisualSettings(_visualSettings);
}

void MainWindow::createActions()
{
	QMenu* actionMenu = menuBar()->addMenu(tr("&Actions"));
	QToolBar* actionBar = addToolBar(tr("Actions"));
	actionBar->setIconSize(QSize(24, 24));

	_startDinnerAct = new QAction(QIcon(":/resources/start.png"), tr("&Start Dinner"), this);
	_startDinnerAct->setToolTip(tr("Let the dinner begins"));
	actionMenu->addAction(_startDinnerAct);
	actionBar->addAction(_startDinnerAct);

	_stopDinnerAct = new QAction(QIcon(":/resources/stop.png"), tr("Sto&p Dinner"), this);
	_stopDinnerAct->setToolTip(tr("Enough of this nonsense"));
	actionMenu->addAction(_stopDinnerAct);
	actionBar->addAction(_stopDinnerAct);

	_settingsAct = new QAction(QIcon(":/resources/settings.png"), tr("Se&ttings..."), this);
	_settingsAct->setToolTip(tr("Settings"));
	actionMenu->addAction(_settingsAct);
	actionBar->addAction(_settingsAct);
	connect(_settingsAct, &QAction::triggered, this, &MainWindow::openSettingsDialog);

	actionMenu->addSeparator();

	QAction* exitAct = new QAction(QIcon(":/resources/exit.png"), tr("&Exit"), this);
	exitAct->setToolTip(tr("Go away"));
	connect(exitAct, SIGNAL(triggered()), SLOT(close()));
	actionMenu->addAction(exitAct);

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	QAction* aboutAct = new QAction(QIcon(":/resources/philosophy.png"), tr("A&bout..."), this);
	connect(aboutAct, &QAction::triggered, this, &MainWindow::openAbout);

	QAction* aboutQtAct = new QAction(QIcon(":/resources/qt_logo.png"), tr("About &Qt..."), this);
	connect(aboutQtAct, &QAction::triggered, this, &MainWindow::openAboutQt);

	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}

void MainWindow::createWidgets()
{
	_splitter = new QSplitter(Qt::Horizontal, this);

	_dinnerView = new QGraphicsView(this);
	_dinnerView->setDragMode(QGraphicsView::NoDrag);
	_dinnerView->setAlignment(Qt::AlignCenter);
	_dinnerView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	_sceneManager = new DinnerSceneManager(_dinnerSettings.philNum, _sceneSettings,
											_visualSettings, this);
	_dinnerView->setScene(_sceneManager->scene());

	_logWidget = new LogWidget(this);

	_splitter->addWidget(_dinnerView);
	_splitter->addWidget(_logWidget);
	_splitter->setSizes({static_cast<int>(_availGeometry.width() * 0.7),
						 static_cast<int>(_availGeometry.width() * 0.3)});
}

void MainWindow::createDinner()
{
	_dinner = new Dinner(_dinnerSettings, this);
	connect(_startDinnerAct, SIGNAL(triggered()), _dinner, SLOT(start()));
	connect(_stopDinnerAct, SIGNAL(triggered()), _dinner, SLOT(stop()));
	connect(_dinner, &Dinner::philosopherStatus, _logWidget, &LogWidget::philStatusChanged);
	connect(_dinner, &Dinner::philosopherStatus, _sceneManager, &DinnerSceneManager::philStatusChanged);
	connect(_dinner, &Dinner::forkStatus, _sceneManager, &DinnerSceneManager::forkStatusChanged);
}

void MainWindow::openSettingsDialog()
{
	SettingsDialog* dialog = new SettingsDialog(_dinnerSettings, _sceneSettings,
												_visualSettings, this);
	if (dialog->exec() == QDialog::Accepted)
	{
		DinnerSettings newDinSet = dialog->dinnerSettings();
		if (newDinSet != _dinnerSettings)
		{
			_dinnerSettings = newDinSet;
			delete _dinner;
			createDinner();
		}

		_sceneSettings = dialog->sceneSettings();
		_visualSettings = dialog->visualSettings();

		_sceneManager->setPhilNum(_dinnerSettings.philNum);
		_sceneManager->setSceneSettings(_sceneSettings);
		_sceneManager->setVisualSettings(_visualSettings);
	};

	dialog->deleteLater();
}

QRect MainWindow::findAvailableWindowGeometry()
{
	const QRect& avGeom = qApp->primaryScreen()->availableGeometry();
	const QSize size(avGeom.width() * 0.4, avGeom.height() * 0.5);

	return QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size, avGeom);
}