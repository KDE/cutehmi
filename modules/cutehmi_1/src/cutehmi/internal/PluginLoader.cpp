#include "../../../include/cutehmi/internal/PluginLoader.hpp"

#include <QDir>
#include <QtDebug>
#include <QCoreApplication>
#include <QLibraryInfo>

namespace cutehmi {
namespace internal {

PluginLoader::PluginLoader(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

PluginLoader::~PluginLoader()
{
	unloadPlugins();
}

Plugin * PluginLoader::loadPlugin(const QString & binary, int reqMinor) noexcept(false)
{
	Plugin::MetaData meta = metaData(binary);

	// Make an attempt to obtain version information from meta data.
	if (meta.minor == -1)
		CUTEHMI_LOG_WARNING("Loading plugin '" << binary <<"', which has undefined minor version. Required minor is '" << reqMinor << "'.");
	else if (meta.minor < reqMinor)
		throw WrongVersionException(binary, reqMinor, meta.minor);

	std::unique_ptr<QPluginLoader> loader(new QPluginLoader(binary));
	if (!loader->isLoaded()) {
		if (loader->load()) {
			Plugin * plugin = new Plugin(binary, std::move(loader), meta);
			CUTEHMI_LOG_DEBUG("Loaded plugin '" << binary << "' version '" << plugin->version() << "'.");
			m->loadedPlugins.append(plugin);
		} else
			throw FailedLoadException(binary);
	} else {
		CUTEHMI_LOG_DEBUG("Plugin '" << binary << "' already loaded.");
		if (!plugin(binary))
			m->loadedPlugins.append(new Plugin(binary, std::move(loader), meta));
	}
	return plugin(binary);
}

void PluginLoader::unloadPlugins()
{
	while (!m->loadedPlugins.isEmpty())
		m->loadedPlugins.takeLast()->deleteLater();
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
	std::unique_ptr<QPluginLoader> loader(new QPluginLoader(binary));
	Plugin::MetaData metaData;
	QJsonObject jsonMetaData = loader->metaData().value("MetaData").toObject();

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
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
