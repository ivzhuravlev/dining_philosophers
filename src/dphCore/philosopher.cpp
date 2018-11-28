#include "philosopher.h"
#include <QThread>

using namespace dph;

Philosopher::Philosopher(QMutex& leftFork, QMutex& rightFork, QSemaphore& footMan,
						PhilParameters params) :
	_leftFork(leftFork),
	_rightFork(rightFork),
	_footMan(footMan),
	_stopFlag(false),
	_params(params)
	{}
	
void Philosopher::start()
{
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
}

void Philosopher::getForks()
{
	emit status(PhilosopherEvent::Waiting);
	
	_leftFork.lock();
	emit status(PhilosopherEvent::LeftForkTaken);
	
	_rightFork.lock();
	emit status(PhilosopherEvent::RightForkTaken);
}

void Philosopher::eat()
{
	emit status(PhilosopherEvent::Eating);
	QThread::msleep(_params.eatDuration.count());
}

void Philosopher::putForks()
{
	_leftFork.unlock();
	emit status(PhilosopherEvent::LeftForkReleased);
	
	_rightFork.unlock();
	emit status(PhilosopherEvent::RightForkReleased);
}

void Philosopher::think()
{
	emit status(PhilosopherEvent::Thinking);
	QThread::msleep(_params.thinkDuration.count());
}

