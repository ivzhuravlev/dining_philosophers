#include <QMainWindow>

namespace dph
{
	class Dinner;
}

using dph::Dinner;

class QRect;
class LogWidget;
class QAction;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);

private:
	void createActions();
	void createWidgets();
	QRect findAvailableWindowGeometry();

	LogWidget*		_logWidget;
	Dinner*	_dinner;
	QAction*		_startDinnerAct;
	QAction*		_stopDinnerAct;
};