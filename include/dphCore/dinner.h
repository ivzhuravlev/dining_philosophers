#pragma once

#include "status.h"
#include "philevent.h"
#include "dinnersettings.h"

#include <QObject>
#include <QVector>
#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include <memory>
#include <vector>

namespace dph
{
	class Philosopher;
	
	class Dinner : public QObject
	{
		Q_OBJECT
		
	public:
		Dinner(const DinnerSettings& settings, QObject* parent = nullptr);
		~Dinner();
		
	public slots:
		void start();
		void stop();
			
	signals:
		void philosopherStatus(int p, PhilosopherStatus pStat);
		void forkStatus(int f, ForkStatus fStat);
			
	private slots:
		void receivedEvent(PhilosopherEvent e);
		
	private:
		void init();
		QMutex* leftFork(int phil);
		QMutex* rightFork(int phil);
		
		DinnerSettings						_settings;
		QVector<QThread*>					_threads;
		QVector<Philosopher*>				_philosophers;
		std::vector<std::unique_ptr<QMutex>>	_forks;
		std::unique_ptr<QSemaphore>			_footMan;
		
	};
}
