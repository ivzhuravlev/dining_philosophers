#include "philosopher.h"
#include <QThread>

using namespace dph;

Philosopher::Philosopher(QMutex* leftFork, QMutex* rightFork, QSemaphore* footMan,
						PhilParameters params, QObject* parent) :
	QObject(parent),
	_leftFork(leftFork),
	_rightFork(rightFork),
	_footMan(footMan),
	_stopFlag(false),
	_params(params)
	{
	}
	
void Philosopher::start()
{
	_stopFlag.store(false);
	process();
}
	
void Philosopher::stop()
{
	_stopFlag.store(true);
}

void Philosopher::process()
{
	while(!_stopFlag.load())
	{
		think();
		getForks();
		eat();
		putForks();
	}
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, Finished));
	emit finished();
}

void Philosopher::getForks()
{
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, Waiting));
	
	_footMan->acquire();

	_leftFork->lock();
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, LeftForkTaken));
	
	_rightFork->lock();
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, RightForkTaken));
}

void Philosopher::eat()
{
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, Eating));
	QThread::msleep(_params.eatDuration.count());
}

void Philosopher::putForks()
{
	_leftFork->unlock();
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, LeftForkReleased));
	
	_rightFork->unlock();
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, RightForkReleased));

	_footMan->release();
}

void Philosopher::think()
{
	emit sendEvent(PhilosopherEvent(_params.ordinalNumber, Thinking));
	QThread::msleep(_params.thinkDuration.count());
}

