#include "dinnerscenemanager.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QtMath>

using namespace dph;

DinnerSceneManager::DinnerSceneManager(int philNum, QObject* parent) :
	QObject(parent),
	_philNum(philNum)
{
	_scene = new QGraphicsScene(this);

	setColorMaps();

	QPen pen(Qt::black);
	QBrush pBrush(_philColorMap[PhilosopherStatus::Finish]);
	QBrush fBrush(_forkColorMap[ForkStatus::Available]);

	const int xC = 0;
	const int yC = 0;
	const int rEllipse = 60;
	const int fW = 10;
	const int fH = 50;
	const int R = 150;
	const double phi0 = -M_PI_2;
	for (int i = 0; i < philNum; ++i)
	{
		double phi1 = 2 * M_PI * i / philNum;
		QPoint ellPoint(xC + R * qCos(phi0 + phi1), yC + R * qSin(phi0 + phi1));
		QPoint ellOffset(-rEllipse / 2, -rEllipse / 2);
		QSize  ellSize(rEllipse, rEllipse);

		auto ellipse =  _scene->addEllipse(QRectF(ellPoint + ellOffset, ellSize), pen, pBrush);
		_philosophers.append(ellipse);

		QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(i), ellipse);
		text->setFont(QFont("Times", 14, QFont::DemiBold));
		QRectF textRect = text->boundingRect();
		QPointF textOffset(-textRect.width() / 2, -textRect.height() / 2);
		text->setPos(ellPoint + textOffset);

		double phi2 = (2 * i + 1) * M_PI / philNum;
		QPoint forkPoint(xC + R * qCos(phi0 + phi2), yC + R * qSin(phi0 + phi2));
		QPoint forkOffset(-fW / 2, -fH / 2);
		QSize  forkSize(fW, fH);

		auto fork = _scene->addRect(QRectF(forkPoint + forkOffset, forkSize), pen, fBrush);
		fork->setTransformOriginPoint(forkPoint);
		fork->setRotation((phi2 / M_PI - 1.) * 180.);
		_forks.append(fork);
	}
}

QGraphicsScene* DinnerSceneManager::scene() const
{
	return _scene;
}

void DinnerSceneManager::philStatusChanged(int p, PhilosopherStatus pStat)
{
	if (p >= _philNum)
		return;
	
	_philosophers[p]->setBrush(QBrush(_philColorMap[pStat]));
}

void DinnerSceneManager::forkStatusChanged(int p, ForkStatus fStat)
{
	if (p >= _philNum)
		return;

	_forks[p]->setBrush(QBrush(_forkColorMap[fStat]));
}

void DinnerSceneManager::setColorMaps()
{
	_philColorMap[PhilosopherStatus::Think] = QColor(qRgb(51, 51, 255));	//blue
	_philColorMap[PhilosopherStatus::Eat] = QColor(qRgb(0, 153, 51));		//green
	_philColorMap[PhilosopherStatus::Wait] = QColor(qRgb(204, 0, 0));		//red
	_philColorMap[PhilosopherStatus::Finish] = QColor(qRgb(255, 163, 26));	//orange

	_forkColorMap[ForkStatus::Available] = QColor(qRgb(0, 153, 51));	//green
	_forkColorMap[ForkStatus::Occupied] = QColor(qRgb(204, 0, 0));		//red
}
