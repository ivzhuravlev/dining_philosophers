#pragma once

#include <QWidget>

class QSpinBox;
namespace dph
{
	struct DinnerSettings;
}

using dph::DinnerSettings;

class DinnerSettingsWidget : public QWidget
{
	Q_OBJECT
public:
	DinnerSettingsWidget(DinnerSettings def, QWidget* parent = nullptr);
	DinnerSettings dinnerSettings() const;
	void setDefault();
private:
	QSpinBox* _numSpin;
	QSpinBox* _eatSpin;
	QSpinBox* _thinkSpin;
};