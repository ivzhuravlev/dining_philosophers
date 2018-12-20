#include "settingsdialog.h"
#include "settings.h"
#include "dphCore/dinnersettings.h"
#include "dinnersettingswidget.h"
#include "scenesettingswidget.h"
#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

SettingsDialog::SettingsDialog()
{
	_listWidget = new QListWidget(this);
	_listWidget->setViewMode(QListView::IconMode);
	_listWidget->setIconSize(QSize(48, 48));
	_listWidget->setMovement(QListView::Static);
	_listWidget->setFlow(QListView::LeftToRight);
	_listWidget->setSpacing(12);
	_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_listWidget->setFixedSize(300, 96);
	createIcons();
	_listWidget->setCurrentRow(0);

	connect(_listWidget, &QListWidget::currentItemChanged, this, &SettingsDialog::changePage);

	_stackWidget = new QStackedWidget(this);
	_stackWidget->addWidget(new DinnerSettingsWidget(DinnerSettings(), _stackWidget));
	_stackWidget->addWidget(new SceneSettingsWidget(SceneSettings(), _stackWidget));
	_stackWidget->setCurrentIndex(0);
	
	QVBoxLayout* widgLay = new QVBoxLayout();
	widgLay->addWidget(_listWidget);
//	widgLay->addStretch(1);
	widgLay->addWidget(_stackWidget);

	QPushButton* okBtn = new QPushButton(tr("OK"), this);
	QPushButton* cancelBtn = new QPushButton(tr("Cancel"), this);
	connect(cancelBtn, &QPushButton::clicked, this, &QDialog::close);

	QHBoxLayout* butLay = new QHBoxLayout();
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
