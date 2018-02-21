#include "../../include/cutehmi/PluginLoader.hpp"

#include <QDir>
#include <QtDebug>
#include <QCoreApplication>
#include <QLibraryInfo>

namespace cutehmi {

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

Plugin * PluginLoader::loadPlugin(const QString & binary, int reqMinor)
{
	Plugin::MetaData meta = metaData(binary);

	// Make an attempt to obtain version information from meta data.
	if (meta.minor == -1)
		CUTEHMI_LOG_WARNING("Loading plugin '" << binary <<"', which has undefined minor version. Required minor is '" << reqMinor << "'.");
	else if (meta.minor < reqMinor)
		throw WrongVersionException(binary, reqMinor, meta.minor);

	m->loader.setFileName(binary);
	if (!m->loader.isLoaded()) {
		QObject * instance = m->loader.instance();
		if (instance) {
			Plugin * plugin = new Plugin(binary, instance, meta);
			CUTEHMI_LOG_DEBUG("Loaded plugin '" << binary << "' version '" << plugin->version() << "'.");
			m->loadedPlugins.append(plugin);
		} else
			throw FailedLoadException(binary);
	} else {
		CUTEHMI_LOG_DEBUG("Plugin '" << binary << "' already loaded.");
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
			CUTEHMI_LOG_DEBUG("Unloaded plugin '" << plugin->binary() << "'.");
		else
			CUTEHMI_LOG_DEBUG("Could not unload plugin '" << plugin->binary() << "'.");
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
	QJsonObject jsonMetaData = m->loader.metaData().value("MetaData").toObject();

	QStringList unavailableMetaData;
	if (jsonMetaData.value("id").isUndefined())
		unavailableMetaData << "id";
	if (jsonMetaData.value("name").isUndefined())
		unavailableMetaData << "name";
	if (jsonMetaData.value("minor").isUndefined())
		unavailableMetaData << "minor";
	if (jsonMetaData.value("micro").isUndefined())
		unavailableMetaData << "micro";
	if (!unavailableMetaData.isEmpty())
		CUTEHMI_LOG_WARNING("Plugin '" << binary <<"' is missing '" << unavailableMetaData.join("', '") << "' meta-data information.");

	metaData.id = jsonMetaData.value("id").toString();
	metaData.name = jsonMetaData.value("name").toString();
	metaData.minor = jsonMetaData.value("minor").toInt(-1);
	metaData.micro = jsonMetaData.value("micro").toInt(-1);

	return metaData;
}

}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
