#include "PluginLoader.hpp"

#include <QDir>
#include <QtDebug>
#include <QCoreApplication>
#include <QLibraryInfo>

namespace cutehmi {
namespace base {

QString PluginLoader::Error::str() const
{
	switch (code()) {
		case FAIL_LOAD:
			return tr("Failed to load plugin.");
		case WRONG_VERSION:
			return tr("Wrong plugin version.");
		default:
			return base::Error::str();
	}
}

PluginLoader::PluginLoader():
	m_pluginsDir(QCoreApplication::libraryPaths().first())
{
}

PluginLoader::PluginLoader(const QString & pluginsDir)
{
	setPluginsDir(pluginsDir);
}

PluginLoader::~PluginLoader()
{
	unloadPlugins();
}

void PluginLoader::setPluginsDir(const QString & pluginsDir)
{
	m_pluginsDir = pluginsDir;
	QCoreApplication::addLibraryPath(pluginsDir);
}

const QStringList & PluginLoader::loadedPlugins() const
{
	return m_loadedPlugins;
}

void PluginLoader::loadPlugins()
{
	QDir dir(m_pluginsDir);
	qDebug() << "Looking for plugins in " << dir.canonicalPath() << " directory.";

	for (auto name : dir.entryList(QDir::Files)) {
		m_loader.setFileName(dir.absoluteFilePath(name));
		QObject * plugin = m_loader.instance();
		if (plugin) {
			qDebug() << "Loaded plugin: " << name << ".";
			m_loadedPlugins += name;
		}
	}
}

PluginLoader::Error PluginLoader::loadPlugin(const QString & name, const QString & reqVersion)
{
	// Make an attempt to obtain version information from meta data.
	QString version = pluginVersion(name);
	if (!version.isEmpty())
		if (!checkVersion(version, reqVersion))
			return Error::WRONG_VERSION;

	m_loader.setFileName(name);
	if (m_loader.isLoaded()) {
		qDebug() << "Plugin: " << name << " version: " << version << " already loaded.";
		return Error::OK;
	}
	QObject * plugin = m_loader.instance();
	if (plugin) {
		qDebug() << "Loaded plugin: " << name << " version: " << version << ".";
		m_loadedPlugins += name;
		return Error::OK;
	}
	return Error::FAIL_LOAD;
}

void PluginLoader::unloadPlugins()
{
	for (auto name : m_loadedPlugins) {
		m_loader.setFileName(name);
		if (m_loader.unload())
			qDebug() << "Unloaded plugin: " << name << ".";
	}
	m_loadedPlugins.clear();
}

QString PluginLoader::pluginVersion(const QString & name)
{
	m_loader.setFileName(name);
	return m_loader.metaData().value("MetaData").toObject().value("Version").toString();
}

bool PluginLoader::uiPlugin(const QString & name, QString & uiName, QString & uiVersion)
{
	m_loader.setFileName(name);
	QJsonValue uiPlugin = m_loader.metaData().value("MetaData").toObject().value("UIPlugin");
	if (uiPlugin == QJsonValue::Undefined)
		return false;
	uiName = uiPlugin.toObject().value("Name").toString();
	if (QLibraryInfo::isDebugBuild())
		uiName.append('d');
	uiVersion = uiPlugin.toObject().value("Version").toString();
	return true;
}

QObject * PluginLoader::instance(const QString & name)
{
	m_loader.setFileName(name);
	if (!m_loader.isLoaded())
		return nullptr;
	return m_loader.instance();
}

bool PluginLoader::checkVersion(const QString & pluginVersion, const QString & reqVersion)
{
	int pluginMajor;
	int pluginMinor;
	int pluginMicro;
	int reqMajor;
	int reqMinor;
	int reqMicro;
	parseVersion(pluginVersion, pluginMajor, pluginMinor, pluginMicro);
	parseVersion(reqVersion, reqMajor, reqMinor, reqMicro);

	// Incompatible version.
	if (reqMajor != pluginMajor)
		return false;

	// Too old interface.
	if (reqMinor > pluginMinor)
		return false;

	return true;
}

void PluginLoader::parseVersion(const QString & version, int & major, int & minor, int & micro)
{
	QStringList mmm = version.split(".");
	major = mmm.value(0).toInt();
	minor = mmm.value(1).toInt();
	micro = mmm.value(2).toInt();
}

}
}
