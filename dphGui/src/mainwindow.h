#include <QMainWindow>
#include "settings.h"
#include "dphCore/dinnersettings.h"

namespace dph
{
	class Dinner;
}

using dph::Dinner;
using dph::DinnerSettings;

class SettingsSerializer;
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

protected:
	void closeEvent(QCloseEvent* override);

private:
	void loadSettings();
	void saveSettings();
	void createActions();
	void createWidgets();
	void createDinner();
	QRect findAvailableWindowGeometry();

	QSplitter*		_splitter;
	QGraphicsView*	_dinnerView;
	LogWidget*		_logWidget;
	DinnerSceneManager* _sceneManager;
	Dinner*			_dinner;
	QAction*		_startDinnerAct;
	QAction*		_stopDinnerAct;
	QRect			_availGeometry;
	DinnerSettings	_dinnerSettings;
	SceneSettings	_sceneSettings;
	VisualSettings	_visualSettings;
	SettingsSerializer* _settingsSerializer;
};