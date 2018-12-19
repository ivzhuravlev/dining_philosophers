#pragma once
#include "dphCore/status.h"
#include "settings.h"

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
	DinnerSceneManager(int philNum,
						const SceneSettings& sceneSet,
						const VisualSettings& visSet,
						QObject* parent = nullptr);
	QGraphicsScene* scene() const;

public slots:
	void philStatusChanged(int p, PhilosopherStatus pStat);
	void forkStatusChanged(int p, ForkStatus fStat);

private:
	int _philNum;
	QGraphicsScene* _scene;
	QVector<QGraphicsEllipseItem*>	_philosophers;
	QVector<QGraphicsRectItem*>		_forks;
	SceneSettings	_sceneSettings;
	VisualSettings	_visualSettings;
};