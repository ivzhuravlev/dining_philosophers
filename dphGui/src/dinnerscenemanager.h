#pragma once

#include <QObject>
#include <QVector>

class QGraphicsEllipseItem;
class QGraphicsScene;

class DinnerSceneManager : public QObject
{
	Q_OBJECT
public:
	DinnerSceneManager(/*QRectF sceneSize, */int philNum = 5, QObject* parent = nullptr);
	QGraphicsScene* scene() const;

private:
	int _philNum;
	QGraphicsScene* _scene;
	QVector<QGraphicsEllipseItem*> _philosophers;

};