#pragma once

#include "settings.h"
#include <QWidget>

class QLabel;
struct VisualSettings;

class VisualSettingsWidget : public QWidget
{
	Q_OBJECT
public:
	VisualSettingsWidget(const VisualSettings& def, QWidget* parent = nullptr);
	VisualSettings visualSettings() const;

private:
	QString fontToString(const QFont& font) const;

	VisualSettings _result;

	QLabel* _waitColorLbl;
	QLabel* _eatColorLbl;
	QLabel* _thinkColorLbl;
	QLabel* _finishColorLbl;
	QLabel* _availColorLbl;
	QLabel* _occupyColorLbl;
	QLabel* _fontLbl;
};