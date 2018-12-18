#include "dinnerscenemanager.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>
#include <QtMath>

using namespace dph;

DinnerSceneManager::DinnerSceneManager(int philNum, QObject* parent) :
	QObject(parent),
	_philNum(philNum)
{
	_scene = new QGraphicsScene(this);

	setColorMaps();

	QPen pen(Qt::black);
	QBrush pBrush(QColor(qRgb(155, 155, 155))); // grey
	QBrush fBrush(_forkColorMap[ForkStatus::Available]); // grey

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
		int x = xC + R * qCos(phi0 + phi1);
		int y = yC + R * qSin(phi0 + phi1);
		auto ellipse =  _scene->addEllipse(QRectF(x - rEllipse / 2, y - rEllipse /2, rEllipse, rEllipse), pen, pBrush);
		_philosophers.append(ellipse);

		QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(i), ellipse);
		text->setFont(QFont("Times", 14, QFont::DemiBold));
		text->setPos(x - text->boundingRect().width() / 2, y - text->boundingRect().height() / 2);

		double phi2 = (2 * i + 1) * M_PI / philNum;
		int xf = xC + R * qCos(phi0 + phi2);
		int yf = yC + R * qSin(phi0 + phi2);
		auto fork = _scene->addRect(QRectF(xf - fW / 2, yf - fH / 2, fW, fH), pen, fBrush);
		fork->setTransformOriginPoint(QPointF(xf, yf));
		fork->setRotation((phi2 * 180. / M_PI) - 180);
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

	QColor newColor = _philColorMap[pStat];
	
	_philosophers[p]->setBrush(QBrush(newColor));
}

void DinnerSceneManager::forkStatusChanged(int p, ForkStatus fStat)
{
	if (p >= _philNum)
		return;

	QColor newColor = _forkColorMap[fStat];

	_forks[p]->setBrush(QBrush(newColor));
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
