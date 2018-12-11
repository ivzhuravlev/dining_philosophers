#pragma once

#include "status.h"
#include "philevent.h"
#include "philparameters.h"

#include <QObject>
#include <QMutex>
#include <QSemaphore>
#include <atomic>

namespace dph
{
	class Philosopher : public QObject
	{
		Q_OBJECT
		
		public:
			Philosopher(QMutex* leftFork, QMutex* rightFork, QSemaphore* footMan,
						PhilParameters params, QObject* parent = nullptr);
		
		signals:
			void sendEvent(PhilosopherEvent s);
			void finished();
			
		public slots:
			void start();
			void stop();
		
		private:
			void process();
			
			void think();
			void getForks();
			void eat();
			void putForks();
			
			QMutex*		_leftFork;
			QMutex*		_rightFork;
			QSemaphore*	_footMan;
		
			std::atomic<bool> _stopFlag;
			PhilParameters	_params;
	};
}
