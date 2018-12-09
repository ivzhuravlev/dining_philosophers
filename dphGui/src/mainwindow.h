#include <QMainWindow>

class QRect;
class QPlainTextEdit;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);

private:
	void createActions();
	void createWidgets();
	QRect findAvailableWindowGeometry();

	QPlainTextEdit* _logEdit;
};