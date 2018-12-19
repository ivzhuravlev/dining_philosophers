#pragma once
#include "dphCore/status.h"
#include "settings.h"

#include <QObject>
#include <QVector>
#include <QMap>

using dph::PhilosopherStatus;
using dph::ForkStatus;

class QGraphicsScene;
class QGraphicsEllipseItem;
class QGraphicsRectItem;
class QGraphicsTextItem;

class DinnerSceneManager : public QObject
{
	Q_OBJECT
public:
	DinnerSceneManager(int philNum,
						const SceneSettings& sceneSet,
						const VisualSettings& visSet,
						QObject* parent = nullptr);
	QGraphicsScene* scene() const;
	void setPhilNum(int num);
	void setSceneSettings(const SceneSettings& sceneSet);
	void setVisualSettings(const VisualSettings& visSet);

public slots:
	void philStatusChanged(int p, PhilosopherStatus pStat);
	void forkStatusChanged(int p, ForkStatus fStat);

private:
	void populateScene();
	void clearScene();

	int _philNum;
	QGraphicsScene* _scene;
	QVector<QGraphicsEllipseItem*>	_philosophers;
	QVector<QGraphicsTextItem*>		_numbers;
	QVector<QGraphicsRectItem*>		_forks;
	SceneSettings	_sceneSettings;
	VisualSettings	_visualSettings;
};