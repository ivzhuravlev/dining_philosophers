#include "mainwindow.h"

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
	createActions();
	setGeometry(findAvailableWindowGeometry());
}

void MainWindow::createActions()
{
	QMenu* actionMenu = menuBar()->addMenu(tr("&Actions"));
	QToolBar* actionBar = addToolBar(tr("Actions"));

	QAction* startDinnerAct = new QAction(QIcon(":/resources/start.png"), tr("&Start Dinner"), this);
	startDinnerAct->setToolTip(tr("Let the dinner begins"));
	actionMenu->addAction(startDinnerAct);
	actionBar->addAction(startDinnerAct);

	QAction* stopDinnerAct = new QAction(QIcon(":/resources/stop.png"), tr("Sto&p Dinner"), this);
	stopDinnerAct->setToolTip(tr("Enough of this nothingness"));
	actionMenu->addAction(stopDinnerAct);
	actionBar->addAction(stopDinnerAct);

	actionMenu->addSeparator();

	QAction* exitAct = new QAction(QIcon(":/resources/exit.png"), tr("&Exit"), this);
	exitAct->setToolTip(tr("Go away"));
	actionMenu->addAction(exitAct);
}

QRect MainWindow::findAvailableWindowGeometry()
{
	const QRect& avGeom = qApp->primaryScreen()->availableGeometry();
	const QSize size(avGeom.height() * 0.33, avGeom.height() * 0.5);

	return QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size, avGeom);
}