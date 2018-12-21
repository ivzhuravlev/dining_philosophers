#include "dinnerscenemanager.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QtMath>

using namespace dph;

DinnerSceneManager::DinnerSceneManager(int philNum,
										const SceneSettings& sceneSet,
										const VisualSettings& visSet,
										QObject* parent) :
	QObject(parent),
	_philNum(philNum),
	_sceneSettings(sceneSet),
	_visualSettings(visSet)
{
	_scene = new QGraphicsScene(this);
	populateScene();
}

void DinnerSceneManager::populateScene()
{
	QPen pen(Qt::black);
	QBrush pBrush(_visualSettings.philColors[PhilosopherStatus::Finish]);
	QBrush fBrush(_visualSettings.forkColors[ForkStatus::Available]);

	const int xC = 0;
	const int yC = 0;
	const int r = _sceneSettings.philRadius;
	const int R = _sceneSettings.tableRadius;
	const int fW = _sceneSettings.forkWidth;
	const int fH = _sceneSettings.forkHeight;
	const double phi0 = -M_PI_2;

	for (int i = 0; i < _philNum; ++i)
	{
		double phi1 = 2 * M_PI * i / _philNum;
		QPoint ellPoint(xC + R * qCos(phi0 + phi1), yC + R * qSin(phi0 + phi1));
		QPoint ellOffset(-r / 2, -r / 2);
		QSize  ellSize(r, r);

		auto ellipse = _scene->addEllipse(QRectF(ellPoint + ellOffset, ellSize), pen, pBrush);
		_philosophers.append(ellipse);

		QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(i), ellipse);
		text->setFont(_visualSettings.font);
		QRectF textRect = text->boundingRect();
		QPointF textOffset(-textRect.width() / 2, -textRect.height() / 2);
		text->setPos(ellPoint + textOffset);
		_numbers.append(text);

		double phi2 = (2 * i + 1) * M_PI / _philNum;
		QPoint forkPoint(xC + R * qCos(phi0 + phi2), yC + R * qSin(phi0 + phi2));
		QPoint forkOffset(-fW / 2, -fH / 2);
		QSize  forkSize(fW, fH);

		auto fork = _scene->addRect(QRectF(forkPoint + forkOffset, forkSize), pen, fBrush);
		fork->setTransformOriginPoint(forkPoint);
		fork->setRotation((phi2 / M_PI - 1.) * 180.);
		_forks.append(fork);
	}
}

void DinnerSceneManager::clearScene()
{
	_philosophers.clear();
	_numbers.clear();
	_forks.clear();

	QList<QGraphicsItem*> items = _scene->items();
	for (auto item : items)
	{
		_scene->removeItem(item);
		delete item;
	}
}

QGraphicsScene* DinnerSceneManager::scene() const
{
	return _scene;
}

void DinnerSceneManager::setPhilNum(int num)
{
	if (_philNum == num)
		return;

	clearScene();
	_philNum = num;
	populateScene();
}

void DinnerSceneManager::setSceneSettings(const SceneSettings& sceneSet)
{
	if (_sceneSettings == sceneSet)
		return;

	clearScene();
	_sceneSettings = sceneSet;
	populateScene();
}

void DinnerSceneManager::setVisualSettings(const VisualSettings& visSet)
{
	if (_visualSettings == visSet)
		return;

	_visualSettings = visSet;
	_scene->invalidate();
}

void DinnerSceneManager::philStatusChanged(int p, PhilosopherStatus pStat)
{
	if (p >= _philNum)
		return;
	
	_philosophers[p]->setBrush(QBrush(_visualSettings.philColors[pStat]));
}

void DinnerSceneManager::forkStatusChanged(int p, ForkStatus fStat)
{
	if (p >= _philNum)
		return;

	p = (p - 1 + _philNum) % _philNum;
	_forks[p]->setBrush(QBrush(_visualSettings.forkColors[fStat]));
}
