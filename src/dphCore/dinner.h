#pragma once

#include "status.h"

#include <QObject>
#include <QVector>
#include <QThread>
#include <QMutex>
#include <memory>

namespace dph
{
	class Philosopher;
	
	class Dinner : public QObject
	{
		Q_OBJECT
		
	public:
		Dinner(int philNum = 5, QObject* parent = nullptr);
		
		void start();
		void stop();
			
	signals:
		void philosopherStatus(int p, PhilosopherStatus pStat);
		void forkStatus(int f, ForkStatus fStat);
			
	private slots:
		void receivedEvent(PhilosopherEvent e);
		
	private:
		void init();
		int leftFork(int phil);
		int rightFork(int phil);
		
		const int _philNum;
		QVector<QThread*>					_threads;
		QVector<Philosopher*>				_philosophers;
		QVector<std::unique_ptr<QMutex>>	_forks;
		std::unique_ptr<QSemaphore>			_footMan;
		
	}
}