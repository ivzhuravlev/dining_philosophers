#pragma once

#include "dphCore/status.h"

#include <QMap>
#include <QColor>
#include <QFont>

using dph::PhilosopherStatus;
using dph::ForkStatus;

struct SceneSettings
{
	SceneSettings(int philRad, int tableRad, int forkW, int forkH) :
		philRadius(philRad),
		tableRadius(tableRad),
		forkWidth(forkW),
		forkHeight(forkH)
	{}

	SceneSettings() :
		SceneSettings(60, 150, 10, 50)
	{}

	int philRadius;
	int tableRadius;
	int forkWidth;
	int forkHeight;
};

inline bool operator==(const SceneSettings& lhs, const SceneSettings& rhs)
{
	return lhs.philRadius == rhs.philRadius &&
		lhs.tableRadius == rhs.tableRadius &&
		lhs.forkWidth == rhs.forkWidth &&
		lhs.forkHeight == rhs.forkHeight;
}

inline bool operator!=(const SceneSettings& lhs, const SceneSettings& rhs)
{
	return !(lhs == rhs);
}

struct VisualSettings
{
	VisualSettings(QMap<PhilosopherStatus, QColor> pColors, 
					QMap<ForkStatus, QColor> fColors, QFont f) :
		philColors(pColors),
		forkColors(fColors),
		font(f)
	{}

	VisualSettings()
	{
		philColors[PhilosopherStatus::Think] = QColor(qRgb(51, 51, 255));	//blue
		philColors[PhilosopherStatus::Eat] = QColor(qRgb(0, 153, 51));		//green
		philColors[PhilosopherStatus::Wait] = QColor(qRgb(204, 0, 0));		//red
		philColors[PhilosopherStatus::Finish] = QColor(qRgb(255, 163, 26));	//orange

		forkColors[ForkStatus::Available] = QColor(qRgb(0, 153, 51));	//green
		forkColors[ForkStatus::Occupied] = QColor(qRgb(204, 0, 0));		//red

		font = QFont("Times", 14, QFont::DemiBold);
	}

	QMap<PhilosopherStatus, QColor> philColors;
	QMap<ForkStatus, QColor> forkColors;
	QFont font;
};

inline bool operator==(const VisualSettings& lhs, const VisualSettings& rhs)
{
	return lhs.philColors == rhs.philColors &&
		lhs.forkColors == rhs.forkColors &&
		lhs.font == rhs.font;
}

inline bool operator!=(const VisualSettings& lhs, const VisualSettings& rhs)
{
	return !(lhs == rhs);
}