#include "dphCore/dinner.h"
#include "dphCore/status.h"
#include "philparameters.h"
#include "philosopher.h"

#include <QThread>
#include <QMutex>
#include <QSemaphore>

using namespace dph;

Dinner::Dinner(const DinnerSettings& settings, QObject* parent) :
	QObject(parent),
	_settings(settings)
	{
		qRegisterMetaType<PhilosopherEvent>("PhilosopherEvent");
		qRegisterMetaType<PhilosopherStatus>("PhilosopherStatus");
		qRegisterMetaType<ForkStatus>("ForkStatus");
		init();
	}
	
void Dinner::init()
{
	const int philNum = _settings.philNum;
	_footMan = std::make_unique<QSemaphore>(philNum - 1);
	
	for(int i = 0; i < philNum; ++i)
	{
		_forks.push_back(std::make_unique<QMutex>());
	}
	
	for(int i = 0; i < philNum; ++i)
	{
		PhilParameters param(i, _settings.eatDur, _settings.thinkDur);
		Philosopher* phil = new Philosopher(leftFork(i), rightFork(i), _footMan.get(), param);
		QThread* thread = new QThread(this);
		
		phil->moveToThread(thread);
		QObject::connect(phil, &Philosopher::sendEvent, this, &Dinner::receivedEvent);
		QObject::connect(thread, &QThread::finished, phil, &QObject::deleteLater);
		
		_threads.append(thread);
		_philosophers.append(phil);
	}

	for(QThread* t : _threads)
		t->start();
}

void Dinner::receivedEvent(PhilosopherEvent e)
{
	switch (e.event)
	{
	case Eating:
		emit philosopherStatus(e.number, PhilosopherStatus::Eat);
		break;
	case Thinking:
		emit philosopherStatus(e.number, PhilosopherStatus::Think);
		break;
	case Waiting:
		emit philosopherStatus(e.number, PhilosopherStatus::Wait);
		break;
	case Finished:
		emit philosopherStatus(e.number, PhilosopherStatus::Finish);
		break;
	case LeftForkTaken:
		emit forkStatus(e.number, ForkStatus::Occupied);
		break;
	case RightForkTaken:
		emit forkStatus((e.number + 1) % _settings.philNum, ForkStatus::Occupied);
		break;
	case LeftForkReleased:
		emit forkStatus(e.number, ForkStatus::Available);
		break;
	case RightForkReleased:
		emit forkStatus((e.number + 1) % _settings.philNum, ForkStatus::Available);
		break;
	}
}

void Dinner::start()
{
	for (Philosopher* ph : _philosophers)
		QMetaObject::invokeMethod(ph, "start", Qt::QueuedConnection);
}

dph::Dinner::~Dinner()
{
	stop();
	for (QThread* t : _threads)
	{
		t->quit();
		t->wait();
	}	
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
	return _forks[(phil + 1) % _settings.philNum].get();
}