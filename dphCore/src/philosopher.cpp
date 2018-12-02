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
	{}
	
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
	emit finished();
}

void Philosopher::getForks()
{
	emit sendEvent(PhilosopherEvent::Waiting);
	
	_leftFork->lock();
	emit sendEvent(PhilosopherEvent::LeftForkTaken);
	
	_rightFork->lock();
	emit sendEvent(PhilosopherEvent::RightForkTaken);
}

void Philosopher::eat()
{
	emit sendEvent(PhilosopherEvent::Eating);
	QThread::msleep(_params.eatDuration.count());
}

void Philosopher::putForks()
{
	_leftFork->unlock();
	emit sendEvent(PhilosopherEvent::LeftForkReleased);
	
	_rightFork->unlock();
	emit sendEvent(PhilosopherEvent::RightForkReleased);
}

void Philosopher::think()
{
	emit sendEvent(PhilosopherEvent::Thinking);
	QThread::msleep(_params.thinkDuration.count());
}

