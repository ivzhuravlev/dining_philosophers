#include "dinnersettingswidget.h"
#include "dphCore/dinnersettings.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>

using namespace dph;

DinnerSettingsWidget::DinnerSettingsWidget(DinnerSettings def, QWidget* parent) :
	QWidget(parent)
{
	QLabel* numLbl = new QLabel(tr("Number of philosophers"), this);
	QSpinBox* _numSpin = new QSpinBox(this);
	_numSpin->setMinimum(4);
	_numSpin->setMaximum(8);
	_numSpin->setValue(def.philNum);

	QHBoxLayout* numLay = new QHBoxLayout();
	numLay->addWidget(numLbl);
	numLay->addWidget(_numSpin);

	QLabel* eatLbl = new QLabel(tr("Time of eating, ms"), this);
	QSpinBox* _eatSpin = new QSpinBox(this);
	_eatSpin->setMinimum(10);
	_eatSpin->setMaximum(10000);
	_eatSpin->setValue(def.eatDur.count());

	QHBoxLayout* eatLay = new QHBoxLayout();
	eatLay->addWidget(eatLbl);
	eatLay->addWidget(_eatSpin);

	QLabel* thinkLbl = new QLabel(tr("Time of thinking, ms"), this);
	QSpinBox* _thinkSpin = new QSpinBox(this);
	_thinkSpin->setMinimum(10);
	_thinkSpin->setMaximum(10000);
	_thinkSpin->setValue(def.thinkDur.count());

	QHBoxLayout* thinkLay = new QHBoxLayout();
	thinkLay->addWidget(thinkLbl);
	thinkLay->addWidget(_thinkSpin);

	QVBoxLayout* dinSetLay = new QVBoxLayout();
	dinSetLay->addLayout(numLay);
	dinSetLay->addLayout(eatLay);
	dinSetLay->addLayout(thinkLay);

	setLayout(dinSetLay);
}

DinnerSettings DinnerSettingsWidget::dinnerSettings() const
{
	DinnerSettings settings(_numSpin->value(), _eatSpin->value(), _thinkSpin->value());
	return settings;
}
