#include "settingsserializer.h"
#include "settings.h"
#include "dphCore/dinnersettings.h"

#include <QSettings>
#include <QString>
#include <QMap>


SettingsSerializer::SettingsSerializer(const QString& orgName,
									   const QString& appName,
									   QObject* parent) :
	QObject(parent),
	_settings(new QSettings(orgName, appName, this))
{

}

void SettingsSerializer::saveWinSettings(const QByteArray & geometry, bool maximized)
{
	_settings->beginGroup("WindowSettings");
	_settings->setValue("Maximized", maximized);
	if (!maximized)
		_settings->setValue("Geometry", geometry);
	_settings->endGroup();
}

void SettingsSerializer::saveDinnerSettings(const DinnerSettings & dinSet)
{
	_settings->beginGroup("DinnerSettings");
	_settings->setValue("PhilNum", dinSet.philNum);
	_settings->setValue("EatDuration", dinSet.eatDur.count());
	_settings->setValue("ThinkDuration", dinSet.thinkDur.count());
	_settings->endGroup();
}

void SettingsSerializer::saveSceneSettings(const SceneSettings & sceneSet)
{
	_settings->beginGroup("SceneSettings");
	_settings->setValue("PhilRadius", sceneSet.philRadius);
	_settings->setValue("TableRadius", sceneSet.tableRadius);
	_settings->setValue("ForkWidth", sceneSet.forkWidth);
	_settings->setValue("ForkHeight", sceneSet.forkHeight);
	_settings->endGroup();
}

void SettingsSerializer::saveVisualSettings(const VisualSettings & visSet)
{
	_settings->beginGroup("VisualSettings");

	QMap<QString, QVariant> philColorMap;

	for (auto k : visSet.philColors.keys())
	{
		philColorMap.insert(QString::number(static_cast<int>(k)), visSet.philColors[k]);
	}

	_settings->setValue("PhilColors", philColorMap);

	QMap<QString, QVariant> forkColorMap;

	for (auto k : visSet.forkColors.keys())
	{
		forkColorMap.insert(QString::number(static_cast<int>(k)), visSet.forkColors[k]);
	}
	_settings->setValue("ForkColors", forkColorMap);

	_settings->setValue("NumberFont", visSet.font.toString());

	_settings->endGroup();
}

QByteArray SettingsSerializer::loadWinSettings(bool& maximized) const
{
	_settings->beginGroup("WindowSettings");
	QByteArray result = _settings->value("Geometry").toByteArray();
	maximized = _settings->value("Maximized").toBool();
	_settings->endGroup();

	return result;
}

DinnerSettings SettingsSerializer::loadDinnerSettings() const
{
	DinnerSettings def;

	_settings->beginGroup("DinnerSettings");
	def.philNum = _settings->value("PhilNum", def.philNum).toInt();
	def.eatDur = std::chrono::milliseconds(_settings->value("EatDuration", def.eatDur.count()).toInt());
	def.thinkDur = std::chrono::milliseconds(_settings->value("ThinkDuration", def.thinkDur.count()).toInt());
	_settings->endGroup();

	return def;
}

SceneSettings SettingsSerializer::loadSceneSettings() const
{
	SceneSettings def;

	_settings->beginGroup("SceneSettings");
	def.philRadius = _settings->value("PhilRadius", def.philRadius).toInt();
	def.tableRadius = _settings->value("TableRadius", def.tableRadius).toInt();
	def.forkWidth = _settings->value("ForkWidth", def.forkWidth).toInt();
	def.forkHeight = _settings->value("ForkHeight", def.forkHeight).toInt();
	_settings->endGroup();

	return def;
}

VisualSettings SettingsSerializer::loadVisualSettings() const
{
	VisualSettings def; 

	_settings->beginGroup("VisualSettings");

	auto philColorMap = _settings->value("PhilColors").toMap();
	if (!philColorMap.isEmpty())
	{
		QMap<dph::PhilosopherStatus, QColor> map;
		for (auto k : philColorMap.keys())
		{
			map.insert(static_cast<dph::PhilosopherStatus>(k.toInt()),
					   philColorMap.value(k).value<QColor>());
		}
		def.philColors = map;
	}

	auto forkColorMap = _settings->value("ForkColors").toMap();
	if (!forkColorMap.isEmpty())
	{
		QMap<dph::ForkStatus, QColor> map;
		for (auto k : forkColorMap.keys())
		{
			map.insert(static_cast<dph::ForkStatus>(k.toInt()),
				forkColorMap.value(k).value<QColor>());
		}
		def.forkColors = map;
	}

	QString fontStr = _settings->value("NumberFont").toString();
	if (!fontStr.isEmpty())
	{
		QFont font;
		font.fromString(fontStr);
		def.font = font;
	}

	_settings->endGroup();

	return def;
}
