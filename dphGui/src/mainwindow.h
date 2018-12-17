#include <QMainWindow>

namespace dph
{
	class Dinner;
}

using dph::Dinner;

class QRect;
class LogWidget;
class DinnerSceneManager;
class QAction;
class QGraphicsView;
class QSplitter;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);

private:
	void createActions();
	void createWidgets();
	QRect findAvailableWindowGeometry();

	QSplitter*		_splitter;
	QGraphicsView*	_dinnerView;
	LogWidget*		_logWidget;
	DinnerSceneManager* _sceneManager;
	Dinner*			_dinner;
	QAction*		_startDinnerAct;
	QAction*		_stopDinnerAct;
	QRect			_availGeometry;
};