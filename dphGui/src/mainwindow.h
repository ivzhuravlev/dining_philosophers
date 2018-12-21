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

private slots:
	void openSettingsDialog();
	void openAbout();
	void openAboutQt();

private:
	void loadSettings();
	void saveSettings();
	void createActions();
	void createWidgets();
	void createDinner();

	QRect findAvailableWindowGeometry();

	QRect _availGeometry;

	QSplitter*		_splitter;
	QGraphicsView*	_dinnerView;
	LogWidget*		_logWidget;

	Dinner*				_dinner;
	DinnerSceneManager* _sceneManager;
	
	QAction*	_startDinnerAct;
	QAction*	_stopDinnerAct;
	QAction*	_settingsAct;
	
	DinnerSettings		_dinnerSettings;
	SceneSettings		_sceneSettings;
	VisualSettings		_visualSettings;
	SettingsSerializer* _settingsSerializer;
};