#include "settingsdialog.h"
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

SettingsDialog::SettingsDialog()
{
	//QWidget* widget = new QWidget(this);
	_listWidget = new QListWidget(this);
	_listWidget->setViewMode(QListView::IconMode);
	_listWidget->setIconSize(QSize(48, 48));
	_listWidget->setMaximumHeight(96);
	_listWidget->setMovement(QListView::Static);
	_listWidget->setFlow(QListView::LeftToRight);
	_listWidget->setSpacing(10);
	_listWidget->setResizeMode(QListView::Adjust);
	_listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

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

	_listWidget->setCurrentRow(0);
//	qDebug() << _listWidget->sizeHintForColumn(0) * _listWidget->count() + 2 * _listWidget->frameWidth();
	//_listWidget->setFixedSize(310, 96);

	QVBoxLayout* widgLay = new QVBoxLayout();
	widgLay->addWidget(_listWidget);

	QPushButton* okBtn = new QPushButton(tr("OK"), this);
	QPushButton* cancelBtn = new QPushButton(tr("Cancel"), this);

	QHBoxLayout* butLay = new QHBoxLayout();
	butLay->addStretch(1);
	butLay->addWidget(okBtn);
	butLay->addWidget(cancelBtn);

	QVBoxLayout* mainLay = new QVBoxLayout();
	mainLay->addLayout(widgLay);
	mainLay->addStretch(1);
	mainLay->addSpacing(12);
	mainLay->addLayout(butLay);

//	setMinimumWidth(400);

	setLayout(mainLay);
	setWindowTitle(tr("Settings"));
}