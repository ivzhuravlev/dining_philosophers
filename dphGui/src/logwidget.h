#pragma once

#include <QTextEdit>
#include "dphCore/status.h"

class LogWidget : public QTextEdit
{
	Q_OBJECT
public:
	LogWidget(QWidget* parent = nullptr);

public slots:
	void philStatusChanged(int p, dph::PhilosopherStatus pStat);
};
