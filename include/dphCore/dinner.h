#pragma once

#include "dphCore_global.h"
#include "philevent.h"
#include "dinnersettings.h"

#include <QObject>
#include <QVector>
#include <memory>
#include <vector>

class QThread;
class QMutex;
class QSemaphore;

namespace dph
{
	class Philosopher;
	enum class PhilosopherStatus;
	enum class ForkStatus;
	
	class DPHCORE_EXPORT Dinner : public QObject
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
