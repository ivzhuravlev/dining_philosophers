#include "settingsdialog.h"
#include "settings.h"
#include "dphCore/dinnersettings.h"
#include "dinnersettingswidget.h"
#include "scenesettingswidget.h"
#include "visualsettingswidget.h"

#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

SettingsDialog::SettingsDialog(dph::DinnerSettings dinSet, SceneSettings sceneSet,
								VisualSettings visSet, QWidget* parent) :
	QDialog(parent)
{
	_listWidget = new QListWidget(this);
	_listWidget->setViewMode(QListView::IconMode);
	_listWidget->setIconSize(QSize(48, 48));
	_listWidget->setMovement(QListView::Static);
	_listWidget->setFlow(QListView::LeftToRight);
	_listWidget->setSpacing(20);
	_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_listWidget->setFixedSize(332, 110);
	createIcons();
	_listWidget->setCurrentRow(0);

	connect(_listWidget, &QListWidget::currentItemChanged, this, &SettingsDialog::changePage);

	_stackWidget = new QStackedWidget(this);

	_dinSetWidget = new DinnerSettingsWidget(dinSet, _stackWidget);
	_sceneSetWidget = new SceneSettingsWidget(sceneSet, _stackWidget);
	_visSetWidget = new VisualSettingsWidget(visSet, _stackWidget);

	_stackWidget->addWidget(_dinSetWidget);
	_stackWidget->addWidget(_sceneSetWidget);
	_stackWidget->addWidget(_visSetWidget);
	_stackWidget->setCurrentIndex(0);
	
	QVBoxLayout* widgLay = new QVBoxLayout();
	widgLay->addWidget(_listWidget);
	widgLay->addWidget(_stackWidget);

	QPushButton* okBtn = new QPushButton(tr("OK"), this);
	okBtn->setDefault(true);
	connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
	QPushButton* cancelBtn = new QPushButton(tr("Cancel"), this);
	connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
	QPushButton* defBtn = new QPushButton(tr("Default"), this);
	connect(defBtn, &QPushButton::clicked, this, &SettingsDialog::setDefault);

	QHBoxLayout* butLay = new QHBoxLayout();
	butLay->addWidget(defBtn);
	butLay->addStretch(1);
	butLay->addWidget(okBtn);
	butLay->addWidget(cancelBtn);

	QVBoxLayout* mainLay = new QVBoxLayout();
	mainLay->addLayout(widgLay);
	mainLay->addStretch(1);
	mainLay->addLayout(butLay);

	setLayout(mainLay);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setWindowTitle(tr("Settings"));
}

DinnerSettings SettingsDialog::dinnerSettings() const
{
	return _dinSetWidget->dinnerSettings();
}

SceneSettings SettingsDialog::sceneSettings() const
{
	return _sceneSetWidget->sceneSettings();
}

VisualSettings SettingsDialog::visualSettings() const
{
	return _visSetWidget->visualSettings();
}

void SettingsDialog::setDefault()
{
	switch (_stackWidget->currentIndex())
	{
	case 0:
		_dinSetWidget->setDefault();
		break;
	case 1:
		_sceneSetWidget->setDefault();
		break;
	case 2:
		_visSetWidget->setDefault();
		break;
	default:
		break;
	}
}

void SettingsDialog::createIcons()
{
	QListWidgetItem *dinnerBtn = new QListWidgetItem(_listWidget);
	dinnerBtn->setIcon(QIcon(":/resources/spaghetti.png"));
	dinnerBtn->setText(tr("Dinner settings"));
	dinnerBtn->setTextAlignment(Qt::AlignHCenter);
	dinnerBtn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *sceneBtn = new QListWidgetItem(_listWidget);
	sceneBtn->setIcon(QIcon(":/resources/geometry.png"));
	sceneBtn->setText(tr("Scene settings"));
	sceneBtn->setTextAlignment(Qt::AlignHCenter);
	sceneBtn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *visBtn = new QListWidgetItem(_listWidget);
	visBtn->setIcon(QIcon(":/resources/palette.png"));
	visBtn->setText(tr("Visual settings"));
	visBtn->setTextAlignment(Qt::AlignHCenter);
	visBtn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void SettingsDialog::changePage(QListWidgetItem* current, QListWidgetItem* previous)
{
	if (!current)
		current = previous;

	_stackWidget->setCurrentIndex(_listWidget->row(current));
}
