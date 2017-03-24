#include "../../include/base/PluginLoader.hpp"

#include <QDir>
#include <QtDebug>
#include <QCoreApplication>
#include <QLibraryInfo>

namespace cutehmi {
namespace base {

PluginLoader::PluginLoader():
	m(new Members(QCoreApplication::libraryPaths().first()))
{
}

PluginLoader::PluginLoader(const QString & pluginsDir):
	m(new Members)
{
	setPluginsDir(pluginsDir);
}

PluginLoader::~PluginLoader()
{
	unloadPlugins();
}

void PluginLoader::setPluginsDir(const QString & pluginsDir)
{
	m->pluginsDir = pluginsDir;
	QCoreApplication::addLibraryPath(pluginsDir);
}

Plugin * PluginLoader::loadPlugin(const QString & binary, const QString & reqVersion)
{
	Plugin::MetaData meta = metaData(binary);

	// Make an attempt to obtain version information from meta data.
	if (!meta.version.isEmpty()) {
		if (!checkVersion(meta.version, reqVersion))
			throw WrongVersionException(binary, reqVersion, meta.version);
	} else
		CUTEHMI_BASE_QWARNING("Loading plugin '" << binary <<"', which has no version information available. Required version is '" << reqVersion << "'.");

	m->loader.setFileName(binary);
	if (!m->loader.isLoaded()) {
		QObject * instance = m->loader.instance();
		if (instance) {
			Plugin * plugin = new Plugin(binary, instance, meta);
			CUTEHMI_BASE_QDEBUG("Loaded plugin '" << binary << "' version '" << meta.version << "'.");
			m->loadedPlugins.append(plugin);
		} else
			throw FailedLoadException(binary);
	} else {
		CUTEHMI_BASE_QDEBUG("Plugin '" << binary << "' version '" << meta.version << "' already loaded.");
		if (!plugin(binary))
			m->loadedPlugins.append(new Plugin(binary, m->loader.instance(), meta));
	}
	return plugin(binary);
}

void PluginLoader::unloadPlugins()
{
	while (!m->loadedPlugins.isEmpty()) {
		Plugin * plugin = m->loadedPlugins.last();
		m->loader.setFileName(plugin->binary());
		if (m->loader.unload())
			CUTEHMI_BASE_QDEBUG("Unloaded plugin '" << plugin->binary() << "'.");
		else
			CUTEHMI_BASE_QDEBUG("Could not unload plugin '" << plugin->binary() << "'.");
		m->loadedPlugins.removeLast();
		plugin->deleteLater();
	}
}

Plugin * PluginLoader::plugin(const QString & binary)
{
	for (auto && plugin : m->loadedPlugins)
		if (plugin->binary() == binary)
			return plugin;
	return nullptr;
}

Plugin::MetaData PluginLoader::metaData(const QString & binary) const
{
	m->loader.setFileName(binary);
	Plugin::MetaData metaData;
	metaData.id = m->loader.metaData().value("MetaData").toObject().value("id").toString();
	metaData.name = m->loader.metaData().value("MetaData").toObject().value("name").toString();
	metaData.version = m->loader.metaData().value("MetaData").toObject().value("version").toString();

	QStringList unavailableMetaData;
	if (metaData.id.isEmpty())
		unavailableMetaData << "'id'";
	if (metaData.name.isEmpty())
		unavailableMetaData << "'name'";
	if (metaData.version.isEmpty())
		unavailableMetaData << "'version'";
	if (!unavailableMetaData.isEmpty())
		CUTEHMI_BASE_QWARNING("Plugin '" << binary <<"' is missing " << unavailableMetaData.join(", ") << " meta-data information.");

	return metaData;
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

PluginLoader::Members::Members(const QString & p_pluginsDir):
	pluginsDir(p_pluginsDir)
{
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
