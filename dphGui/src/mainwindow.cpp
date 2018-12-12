#include "mainwindow.h"
#include "logwidget.h"
#include "dphCore\dinner.h"

#include <QApplication>
#include <QScreen>
#include <QStyle>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QIcon>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent)
{
	createWidgets();
	createActions();

	setCentralWidget(_logWidget);
	setGeometry(findAvailableWindowGeometry());

	_dinner = new Dinner(5, this);
	connect(_startDinnerAct, SIGNAL(triggered()), _dinner, SLOT(start()));
	connect(_stopDinnerAct, SIGNAL(triggered()), _dinner, SLOT(stop()));
	connect(_dinner, &Dinner::philosopherStatus, _logWidget, &LogWidget::philStatusChanged);
}

void MainWindow::createActions()
{
	QMenu* actionMenu = menuBar()->addMenu(tr("&Actions"));
	QToolBar* actionBar = addToolBar(tr("Actions"));

	_startDinnerAct = new QAction(QIcon(":/resources/start.png"), tr("&Start Dinner"), this);
	_startDinnerAct->setToolTip(tr("Let the dinner begins"));
	actionMenu->addAction(_startDinnerAct);
	actionBar->addAction(_startDinnerAct);

	_stopDinnerAct = new QAction(QIcon(":/resources/stop.png"), tr("Sto&p Dinner"), this);
	_stopDinnerAct->setToolTip(tr("Enough of this nothingness"));
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
	_logWidget = new LogWidget(this);
}

QRect MainWindow::findAvailableWindowGeometry()
{
	const QRect& avGeom = qApp->primaryScreen()->availableGeometry();
	const QSize size(avGeom.height() * 0.33, avGeom.height() * 0.5);

	return QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size, avGeom);
}