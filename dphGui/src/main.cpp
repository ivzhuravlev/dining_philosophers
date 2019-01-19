#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("IZhuravlev");
	QCoreApplication::setApplicationName("Dining Philosophers");
	QCoreApplication::setApplicationVersion("1.1.0");

	MainWindow w;
	w.show();
	return app.exec();
}