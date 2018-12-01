#include "dinner.h"

using namespace dph;

Dinner::Dinner(int philNum, QObject* parent) :
	QObject(parent),
	_philNum(philNum)
	{
		init();
	}
	
void Dinner::init()
{
	_footMan = std::make_unique<QSemaphore>(_philNum - 1);
	
	for(int i = 0; i < philNum, ++i)
	{
		_forks.append(std::make_unique<QMutex>());
	}
	
	for(int i = 0; i < philNum, ++i)
	{
		PhilParameters param(i);
		Philosopher* phil = new Philosopher(leftFork(i), rightFork(i), _footMan.get(), param);
		QThread* thread = new QThread(this);
		
		phil->moveToThread(thread);
		QObject::connect(thread, &QThread::started, phil, &Philosopher::start);
		QObject::connect(phil, &Philosopher::sendEvent, this, &Dinner::receivedEvent);
		QObject::connect(phil, &Philosopher::finished, thread, &QThread::quit);
		QObject::connect(thread, &QThread::finished, phil, &QObject::deleteLater);
		
		_threads.append(thread);
		_philosophers.append(phil);
	}
}

void Dinner::start()
{
	for(QThread* t : _threads)
		t->start();
}

void Dinner::stop()
{
	for(Philosopher* ph : _philosophers)
		ph->stop();
}

QMutex* Dinner::leftFork(int phil)
{
	return _forks[phil].get();
}

QMutex* Dinner::rightFork(int phil)
{
	return _forks[(phil + 1) % 5].get();
}