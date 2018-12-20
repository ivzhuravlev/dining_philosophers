#pragma once

#include <QWidget>

class QSpinBox;

struct SceneSettings;

class SceneSettingsWidget : public QWidget
{
	Q_OBJECT
public:
	SceneSettingsWidget(SceneSettings def, QWidget* parent = nullptr);
	SceneSettings sceneSettings() const;
private:
	QSpinBox* _philRadSpin;
	QSpinBox* _tableRadSpin;
	QSpinBox* _forkWSpin;
	QSpinBox* _forkHSpin;
};