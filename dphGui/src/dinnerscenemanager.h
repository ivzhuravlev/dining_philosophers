#pragma once
#include "dphCore/status.h"

#include <QObject>
#include <QVector>
#include <QMap>

using dph::PhilosopherStatus;
using dph::ForkStatus;

class QGraphicsEllipseItem;
class QGraphicsRectItem;
class QGraphicsScene;

class DinnerSceneManager : public QObject
{
	Q_OBJECT
public:
	DinnerSceneManager(int philNum = 5, QObject* parent = nullptr);
	QGraphicsScene* scene() const;

public slots:
	void philStatusChanged(int p, PhilosopherStatus pStat);
	void forkStatusChanged(int p, ForkStatus fStat);

private:
	void setColorMaps();

	int _philNum;
	QGraphicsScene* _scene;
	QVector<QGraphicsEllipseItem*> _philosophers;
	QVector<QGraphicsRectItem*> _forks;
	QMap<PhilosopherStatus, QColor> _philColorMap;
	QMap<ForkStatus, QColor>		_forkColorMap;

};