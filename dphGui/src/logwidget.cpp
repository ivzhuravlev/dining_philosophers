#include "logwidget.h"

using namespace dph;

LogWidget::LogWidget(QWidget* parent) :
	QTextEdit(parent)
{
	setReadOnly(true);
}

void LogWidget::philStatusChanged(int p, PhilosopherStatus pStat)
{
	QString status;
	switch (pStat)
	{
	case PhilosopherStatus::Eat:
		status = tr("eats");
		break;
	case PhilosopherStatus::Think:
		status = tr("thinks");
		break;
	case PhilosopherStatus::Wait:
		status = tr("waits");
		break;
	default:
		break;
	}

	append(QString(tr("Philosopher %1%2 %3")).arg(tr("#"), QString::number(p), status));
}