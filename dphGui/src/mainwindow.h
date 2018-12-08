#include <QMainWindow>

class QRect;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);

private:
	void createActions();
	QRect MainWindow::findAvailableWindowGeometry();
};