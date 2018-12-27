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
#include <QActionGroup>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QIcon>
#include <QSplitter>
#include <QGraphicsView>
#include <QMessageBox>
#include <QDir>
#include <QTranslator>

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
	loadTranslator();
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
	_language = _settingsSerializer->loadLangSettings();
	_dinnerSettings = _settingsSerializer->loadDinnerSettings();
	_sceneSettings = _settingsSerializer->loadSceneSettings();
	_visualSettings = _settingsSerializer->loadVisualSettings();
}

void MainWindow::saveSettings()
{
	_settingsSerializer->saveLangSettings(_language);
	_settingsSerializer->saveDinnerSettings(_dinnerSettings);
	_settingsSerializer->saveSceneSettings(_sceneSettings);
	_settingsSerializer->saveVisualSettings(_visualSettings);
}

void MainWindow::createActions()
{
	_actionMenu = menuBar()->addMenu(QString());
	QToolBar* actionBar = addToolBar(tr("Actions"));
	actionBar->setIconSize(QSize(24, 24));

	_startDinnerAct = new QAction(QIcon(":/resources/start.png"), QString(),this);
	_actionMenu->addAction(_startDinnerAct);
	actionBar->addAction(_startDinnerAct);

	_stopDinnerAct = new QAction(QIcon(":/resources/stop.png"), QString(), this);
	_actionMenu->addAction(_stopDinnerAct);
	actionBar->addAction(_stopDinnerAct);

	_settingsAct = new QAction(QIcon(":/resources/settings.png"), QString(), this);
	_actionMenu->addAction(_settingsAct);
	actionBar->addAction(_settingsAct);
	connect(_settingsAct, &QAction::triggered, this, &MainWindow::openSettingsDialog);

	_actionMenu->addSeparator();

	_exitAct = new QAction(QIcon(":/resources/exit.png"), QString(), this);
	connect(_exitAct, SIGNAL(triggered()), SLOT(close()));
	_actionMenu->addAction(_exitAct);

	_langMenu = menuBar()->addMenu(QString());
	_engAct = new QAction(QIcon(":/resources/usa.png"), QString(), this);
	_engAct->setData("english");
	_engAct->setCheckable(true);
	_rusAct = new QAction(QIcon(":/resources/rus.png"), QString(), this);
	_rusAct->setData("russian");
	_rusAct->setCheckable(true);

	connect(_engAct, &QAction::triggered, this, &MainWindow::loadTranslator);
	connect(_rusAct, &QAction::triggered, this, &MainWindow::loadTranslator);

	QActionGroup* actGroup = new QActionGroup(this);
	actGroup->setExclusive(true);
	actGroup->addAction(_engAct);
	actGroup->addAction(_rusAct);
//	_engAct->setChecked(true);

	_langMenu->addAction(_engAct);
	_langMenu->addAction(_rusAct);

	_helpMenu = menuBar()->addMenu(QString());
	_aboutAct = new QAction(QIcon(":/resources/philosophy.png"), QString(), this);
	connect(_aboutAct, &QAction::triggered, this, &MainWindow::openAbout);

	_aboutQtAct = new QAction(QIcon(":/resources/qt_logo.png"), QString(), this);
	connect(_aboutQtAct, &QAction::triggered, this, &MainWindow::openAboutQt);

	_helpMenu->addAction(_aboutAct);
	_helpMenu->addAction(_aboutQtAct);

	setText();
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

void MainWindow::setText()
{
	this->setWindowTitle(tr("Dining Philosophers"));

	_actionMenu->setTitle(tr("&Actions"));
	_langMenu->setTitle(tr("&Language"));
	_helpMenu->setTitle(tr("&Help"));

	_startDinnerAct->setText(tr("&Start Dinner"));
	_startDinnerAct->setToolTip(tr("Let the dinner begins"));
	_stopDinnerAct->setText(tr("Sto&p Dinner"));
	_stopDinnerAct->setToolTip(tr("Enough of this nonsense"));
	_settingsAct->setText(tr("Se&ttings..."));
	_settingsAct->setToolTip(tr("Settings"));
	_exitAct->setText(tr("&Exit"));
	_exitAct->setToolTip(tr("Go away"));
	_engAct->setText(tr("&English"));;
	_rusAct->setText(tr("&Russian"));;
	_aboutAct->setText(tr("A&bout..."));;
	_aboutQtAct->setText(tr("About &Qt..."));;
}

void MainWindow::loadTranslator()
{
	QString lang;
	QAction* action = qobject_cast<QAction*>(sender());
	if (!action)
		lang = _language.isEmpty() ? "english" : _language;
	else
		lang = action->data().toString();

	QTranslator* translator = new QTranslator(this);
	bool res = translator->load(lang, qApp->applicationDirPath() + "/translations/");
	if (!res)
		return;

	qApp->installTranslator(translator);
	_language = lang;
	if (action)
		action->setChecked(true);

	setText();
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