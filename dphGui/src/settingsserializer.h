#pragma once

#include <QObject>

namespace dph
{
	struct DinnerSettings;
}
struct SceneSettings;
struct VisualSettings;
class QSettings;
class QString;

using dph::DinnerSettings;

class SettingsSerializer : public QObject
{
	Q_OBJECT
public:
	SettingsSerializer(const QString& orgName, const QString& appName, QObject* parent = nullptr);

	void saveWinSettings(const QByteArray& geometry, bool maximized);
	void saveLangSettings(const QString& lang);
	void saveDinnerSettings(const DinnerSettings& dinSet);
	void saveSceneSettings(const SceneSettings& sceneSet);
	void saveVisualSettings(const VisualSettings& visSet);

	QByteArray		loadWinSettings(bool& maximized) const;
	QString			loadLangSettings() const;
	DinnerSettings	loadDinnerSettings() const;
	SceneSettings	loadSceneSettings() const;
	VisualSettings	loadVisualSettings() const;

private:
	QSettings* _settings;

};