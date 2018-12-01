#include "philosopher.h"
#include <QThread>

using namespace dph;

Philosopher::Philosopher(QMutex& leftFork, QMutex& rightFork, QSemaphore& footMan,
						PhilParameters params, QObject* parent = nullptr) :
	QObject(parent)
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
	emit sendEvent(PhilosophersendEvent::Waiting);
	
	_leftFork->lock();
	emit sendEvent(PhilosophersendEvent::LeftForkTaken);
	
	_rightFork->lock();
	emit sendEvent(PhilosophersendEvent::RightForkTaken);
}

void Philosopher::eat()
{
	emit sendEvent(PhilosophersendEvent::Eating);
	QThread::msleep(_params.eatDuration.count());
}

void Philosopher::putForks()
{
	_leftFork->unlock();
	emit sendEvent(PhilosophersendEvent::LeftForkReleased);
	
	_rightFork->unlock();
	emit sendEvent(PhilosophersendEvent::RightForkReleased);
}

void Philosopher::think()
{
	emit sendEvent(PhilosophersendEvent::Thinking);
	QThread::msleep(_params.thinkDuration.count());
}

