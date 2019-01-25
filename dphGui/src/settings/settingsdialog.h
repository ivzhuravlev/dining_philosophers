#pragma once

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

namespace dph
{
	struct DinnerSettings;
}
struct SceneSettings;
struct VisualSettings;

class DinnerSettingsWidget;
class SceneSettingsWidget;
class VisualSettingsWidget;

class SettingsDialog : public QDialog
{
	Q_OBJECT
public:
	SettingsDialog(dph::DinnerSettings dinSet, SceneSettings sceneSet, 
					VisualSettings visSet, QWidget* parent = nullptr);

	dph::DinnerSettings dinnerSettings() const;
	SceneSettings sceneSettings() const;
	VisualSettings visualSettings() const;

private slots:
	void changePage(QListWidgetItem* current, QListWidgetItem* previous);
	void setDefault();

private:
	void createIcons();

	QListWidget*	_listWidget;
	QStackedWidget*	_stackWidget;

	DinnerSettingsWidget*	_dinSetWidget;
	SceneSettingsWidget*	_sceneSetWidget;
	VisualSettingsWidget*	_visSetWidget;
};