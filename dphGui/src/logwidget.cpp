#include "logwidget.h"
#include <QTime>

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
	case PhilosopherStatus::Finish:
		status = tr("finished");
		break;
	default:
		break;
	}

	append(QString(tr("%1 - %2 %3%4 %5")).arg(currentTime(),
												tr("Philosopher"),
												tr("#"),
												QString::number(p),
												status));
}

QString LogWidget::currentTime()
{
	return QTime::currentTime().toString("hh:mm:ss");
}
