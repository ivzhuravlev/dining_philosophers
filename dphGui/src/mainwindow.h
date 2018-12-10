#include <QMainWindow>

class QRect;
class LogWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);

private:
	void createActions();
	void createWidgets();
	QRect findAvailableWindowGeometry();

	LogWidget* _logWidget;
};