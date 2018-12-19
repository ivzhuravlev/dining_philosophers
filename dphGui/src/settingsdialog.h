#pragma once

#include <QDialog>

class QListWidget;
class QStackedWidget;

class SettingsDialog : public QDialog
{
	Q_OBJECT
public:
	SettingsDialog();

private:
	QListWidget*	_listWidget;
	QStackedWidget*	_stackWidget;
};