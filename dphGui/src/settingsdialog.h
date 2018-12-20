#pragma once

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class SettingsDialog : public QDialog
{
	Q_OBJECT
public:
	SettingsDialog();

private slots:
	void changePage(QListWidgetItem* current, QListWidgetItem* previous);

private:
	void createIcons();

	QListWidget*	_listWidget;
	QStackedWidget*	_stackWidget;
};