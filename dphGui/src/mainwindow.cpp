#include "mainwindow.h"
#include "logwidget.h"
#include "dinnerscenemanager.h"
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
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	_availGeometry(findAvailableWindowGeometry())
{
	createWidgets();
	createActions();

	setCentralWidget(_splitter);
	setGeometry(_availGeometry);
	setWindowIcon(QIcon(":/resources/philosophy.png"));

	_dinner = new Dinner(5, this);
	connect(_startDinnerAct, SIGNAL(triggered()), _dinner, SLOT(start()));
	connect(_stopDinnerAct, SIGNAL(triggered()), _dinner, SLOT(stop()));
	connect(_dinner, &Dinner::philosopherStatus, _logWidget, &LogWidget::philStatusChanged);

	//Debug
	connect(_startDinnerAct, &QAction::triggered, [this]()
	{
		qDebug() << _dinnerView->size();
	});
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

	actionMenu->addSeparator();

	QAction* exitAct = new QAction(QIcon(":/resources/exit.png"), tr("&Exit"), this);
	exitAct->setToolTip(tr("Go away"));
	connect(exitAct, SIGNAL(triggered()), SLOT(close()));
	actionMenu->addAction(exitAct);
}

void MainWindow::createWidgets()
{
	_splitter = new QSplitter(Qt::Horizontal, this);

	_dinnerView = new QGraphicsView(this);
	_dinnerView->setDragMode(QGraphicsView::NoDrag);
	QSize size = _dinnerView->size();

	_sceneManager = new DinnerSceneManager(/*QRectF(0, 0, _dinnerView->size().width(), _dinnerView->size().height()),*/ 5, this);
	_dinnerView->setScene(_sceneManager->scene());

	_logWidget = new LogWidget(this);

	_splitter->addWidget(_dinnerView);
	_splitter->addWidget(_logWidget);
	_splitter->setSizes({static_cast<int>(_availGeometry.width() * 0.7),
						 static_cast<int>(_availGeometry.width() * 0.3)});
}

QRect MainWindow::findAvailableWindowGeometry()
{
	const QRect& avGeom = qApp->primaryScreen()->availableGeometry();
	const QSize size(avGeom.width() * 0.4, avGeom.height() * 0.5);

	return QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size, avGeom);
}