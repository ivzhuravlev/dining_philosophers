#include "visualsettingswidget.h"
#include "dphCore/status.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QToolButton>
#include <QPalette>
#include <QColorDialog>
#include <QFontDialog>

using namespace dph;

VisualSettingsWidget::VisualSettingsWidget(const VisualSettings& def, QWidget* parent) :
	QWidget(parent),
	_result(def)
{
	const int frameStyle = QFrame::Raised | QFrame::Panel;

	QGroupBox* philColorBox = new QGroupBox(tr("Philosopher"));
	QGroupBox* forkColorBox = new QGroupBox(tr("Fork"));
	QGroupBox* fontBox = new QGroupBox(tr("Font"));
	QGridLayout* mainLay = new QGridLayout();

	QGridLayout* colorLay = new QGridLayout();
	
	QLabel* waitTextLbl = new QLabel(tr("Waiting"));

	_waitColorLbl = new QLabel();
	
	_waitColorLbl->setFrameStyle(frameStyle);
	_waitColorLbl->setPalette(QPalette(_result.philColors[PhilosopherStatus::Wait]));
	_waitColorLbl->setAutoFillBackground(true);

	QToolButton* waitToolBtn = new QToolButton();
	waitToolBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
	waitToolBtn->setText(tr("..."));
	connect(waitToolBtn, &QToolButton::clicked, [&](bool checked)
	{
		QColor newColor = QColorDialog::getColor(_result.philColors[PhilosopherStatus::Wait],
												 this, tr("Select color"));
		_result.philColors[PhilosopherStatus::Wait] = newColor;
		_waitColorLbl->setPalette(newColor);
	});

	colorLay->addWidget(waitTextLbl, 0, 0);
	colorLay->addWidget(_waitColorLbl, 0, 1);
	colorLay->addWidget(waitToolBtn, 0, 2);
	colorLay->setColumnStretch(0, 1);
	colorLay->setColumnStretch(1, 1);

	QLabel* eatTextLbl = new QLabel(tr("Eating"));

	_eatColorLbl = new QLabel();
	_eatColorLbl->setFrameStyle(frameStyle);
	_eatColorLbl->setPalette(QPalette(_result.philColors[PhilosopherStatus::Eat]));
	_eatColorLbl->setAutoFillBackground(true);

	QToolButton* eatToolBtn = new QToolButton();
	eatToolBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
	eatToolBtn->setText(tr("..."));
	connect(eatToolBtn, &QToolButton::clicked, [&](bool checked)
	{
		QColor newColor = QColorDialog::getColor(_result.philColors[PhilosopherStatus::Eat],
													this, tr("Select color"));
		_result.philColors[PhilosopherStatus::Eat] = newColor;
		_eatColorLbl->setPalette(newColor);
	});

	colorLay->addWidget(eatTextLbl, 1, 0);
	colorLay->addWidget(_eatColorLbl, 1, 1);
	colorLay->addWidget(eatToolBtn, 1, 2);

	QLabel* thinkTextLbl = new QLabel(tr("Thinking"));

	_thinkColorLbl = new QLabel();
	_thinkColorLbl->setFrameStyle(frameStyle);
	_thinkColorLbl->setPalette(QPalette(_result.philColors[PhilosopherStatus::Think]));
	_thinkColorLbl->setAutoFillBackground(true);

	QToolButton* thinkToolBtn = new QToolButton();
	thinkToolBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
	thinkToolBtn->setText(tr("..."));
	connect(thinkToolBtn, &QToolButton::clicked, [&](bool checked)
	{
		QColor newColor = QColorDialog::getColor(_result.philColors[PhilosopherStatus::Think],
													this, tr("Select color"));
		_result.philColors[PhilosopherStatus::Think] = newColor;
		_thinkColorLbl->setPalette(newColor);
	});

	colorLay->addWidget(thinkTextLbl, 2, 0);
	colorLay->addWidget(_thinkColorLbl, 2, 1);
	colorLay->addWidget(thinkToolBtn, 2, 2);

	QLabel* finishTextLbl = new QLabel(tr("Ready"));

	_finishColorLbl = new QLabel();
	_finishColorLbl->setFrameStyle(frameStyle);
	_finishColorLbl->setPalette(QPalette(_result.philColors[PhilosopherStatus::Finish]));
	_finishColorLbl->setAutoFillBackground(true);

	QToolButton* finishToolBtn = new QToolButton();
	finishToolBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
	finishToolBtn->setText(tr("..."));
	connect(finishToolBtn, &QToolButton::clicked, [&](bool checked)
	{
		QColor newColor = QColorDialog::getColor(_result.philColors[PhilosopherStatus::Finish],
													this, tr("Select color"));
		_result.philColors[PhilosopherStatus::Finish] = newColor;
		_finishColorLbl->setPalette(newColor);
	});

	colorLay->addWidget(finishTextLbl, 3, 0);
	colorLay->addWidget(_finishColorLbl, 3, 1);
	colorLay->addWidget(finishToolBtn, 3, 2);

	philColorBox->setLayout(colorLay);

	QGridLayout* forkLay = new QGridLayout();

	QLabel* availTextLbl = new QLabel(tr("Available"));

	_availColorLbl = new QLabel();
	_availColorLbl->setFrameStyle(frameStyle);
	_availColorLbl->setPalette(QPalette(_result.forkColors[ForkStatus::Available]));
	_availColorLbl->setAutoFillBackground(true);

	QToolButton* availToolBtn = new QToolButton();
	availToolBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
	availToolBtn->setText(tr("..."));
	connect(availToolBtn, &QToolButton::clicked, [&](bool checked)
	{
		QColor newColor = QColorDialog::getColor(_result.forkColors[ForkStatus::Available],
			this, tr("Select color"));
		_result.forkColors[ForkStatus::Available] = newColor;
		_availColorLbl->setPalette(newColor);
	});

	forkLay->addWidget(availTextLbl, 0, 0);
	forkLay->addWidget(_availColorLbl, 0, 1);
	forkLay->addWidget(availToolBtn, 0, 2);
	forkLay->setColumnStretch(0, 1);
	forkLay->setColumnStretch(1, 1);

	QLabel* occupyTextLbl = new QLabel(tr("Occupied"));

	_occupyColorLbl = new QLabel();
	_occupyColorLbl->setFrameStyle(frameStyle);
	_occupyColorLbl->setPalette(QPalette(_result.forkColors[ForkStatus::Occupied]));
	_occupyColorLbl->setAutoFillBackground(true);

	QToolButton* occupyToolBtn = new QToolButton();
	occupyToolBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
	occupyToolBtn->setText(tr("..."));
	connect(occupyToolBtn, &QToolButton::clicked, [&](bool checked)
	{
		QColor newColor = QColorDialog::getColor(_result.forkColors[ForkStatus::Occupied],
			this, tr("Select color"));
		_result.forkColors[ForkStatus::Occupied] = newColor;
		_occupyColorLbl->setPalette(newColor);
	});

	forkLay->addWidget(occupyTextLbl, 1, 0);
	forkLay->addWidget(_occupyColorLbl, 1, 1);
	forkLay->addWidget(occupyToolBtn, 1, 2);

	forkColorBox->setLayout(forkLay);

	QHBoxLayout* fontLay = new QHBoxLayout();

	_fontLbl = new QLabel(fontToString(_result.font));

	QToolButton* fontToolBtn = new QToolButton();
	fontToolBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
	fontToolBtn->setText(tr("..."));
	connect(fontToolBtn, &QToolButton::clicked, [&](bool checked)
	{
		bool ok;
		QFont newFont = QFontDialog::getFont(&ok, _result.font, this, tr("Select font"));
		_result.font = newFont;
		_fontLbl->setText(fontToString(newFont));
	});

	fontLay->addWidget(_fontLbl);
	fontLay->addStretch(1);
	fontLay->addWidget(fontToolBtn);

	fontBox->setLayout(fontLay);

	mainLay->addWidget(philColorBox, 0, 0, 3, 1);
	mainLay->addWidget(forkColorBox, 0, 1, 2, 1);
	mainLay->addWidget(fontBox, 2, 1, 1, 1);

	setLayout(mainLay);
}

VisualSettings VisualSettingsWidget::visualSettings() const
{
	return _result;
}

void VisualSettingsWidget::setDefault()
{
	VisualSettings def;
	_waitColorLbl->setPalette(def.philColors[PhilosopherStatus::Wait]);
	_eatColorLbl->setPalette(def.philColors[PhilosopherStatus::Eat]);
	_thinkColorLbl->setPalette(def.philColors[PhilosopherStatus::Think]);
	_finishColorLbl->setPalette(def.philColors[PhilosopherStatus::Finish]);
	_availColorLbl->setPalette(def.forkColors[ForkStatus::Available]);
	_occupyColorLbl->setPalette(def.forkColors[ForkStatus::Occupied]);;
	_fontLbl->setText(fontToString(def.font));
	_result = def;
}

QString VisualSettingsWidget::fontToString(const QFont & font) const
{
	return QString("%1, %2").arg(font.family()).arg(font.pointSize());
}
