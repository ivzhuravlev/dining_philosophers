#include "scenesettingswidget.h"
#include "settings.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>

SceneSettingsWidget::SceneSettingsWidget(SceneSettings def, QWidget* parent) :
	QWidget(parent)
{
	QLabel* philRadLbl = new QLabel(tr("Philosopher circle radius"), this);
	_philRadSpin = new QSpinBox(this);
	_philRadSpin->setMinimum(20);
	_philRadSpin->setMaximum(100);
	_philRadSpin->setValue(def.philRadius);

	QHBoxLayout* philRadLay = new QHBoxLayout();
	philRadLay->addWidget(philRadLbl);
	philRadLay->addWidget(_philRadSpin);

	QLabel* tableRadLbl = new QLabel(tr("Table circle radius"), this);
	_tableRadSpin = new QSpinBox(this);
	_tableRadSpin->setMinimum(100);
	_tableRadSpin->setMaximum(10000);
	_tableRadSpin->setValue(def.tableRadius);

	QHBoxLayout* tableRadLay = new QHBoxLayout();
	tableRadLay->addWidget(tableRadLbl);
	tableRadLay->addWidget(_tableRadSpin);

	QLabel* forkWLbl = new QLabel(tr("Fork width"), this);
	_forkWSpin = new QSpinBox(this);
	_forkWSpin->setMinimum(1);
	_forkWSpin->setMaximum(100);
	_forkWSpin->setValue(def.forkWidth);

	QHBoxLayout* forkWLay = new QHBoxLayout();
	forkWLay->addWidget(forkWLbl);
	forkWLay->addWidget(_forkWSpin);

	QLabel* forkHLbl = new QLabel(tr("Fork height"), this);
	_forkHSpin = new QSpinBox(this);
	_forkHSpin->setMinimum(10);
	_forkHSpin->setMaximum(200);
	_forkHSpin->setValue(def.forkHeight);

	QHBoxLayout* forkHLay = new QHBoxLayout();
	forkHLay->addWidget(forkHLbl);
	forkHLay->addWidget(_forkHSpin);

	QVBoxLayout* dinSetLay = new QVBoxLayout();
	dinSetLay->addLayout(philRadLay);
	dinSetLay->addLayout(tableRadLay);
	dinSetLay->addLayout(forkWLay);
	dinSetLay->addLayout(forkHLay);

	setLayout(dinSetLay);
}

SceneSettings SceneSettingsWidget::sceneSettings() const
{
	SceneSettings settings(_philRadSpin->value(), _tableRadSpin->value(),
						   _forkWSpin->value(), _forkHSpin->value());
	return settings;
}