#include "dinnerscenemanager.h"
#include <QGraphicsScene>

DinnerSceneManager::DinnerSceneManager(/*QRectF sceneSize, */int philNum, QObject* parent) :
	QObject(parent),
	_philNum(philNum)
{
	_scene = new QGraphicsScene(/*sceneSize, */this);
	QPen pen(Qt::black);
	QBrush brush(Qt::green);
	_scene->addEllipse(QRectF(0, 0, 50, 50), pen, brush);
}

QGraphicsScene* DinnerSceneManager::scene() const
{
	return _scene;
}
