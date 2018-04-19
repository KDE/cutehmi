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
	Plugin::Metadata meta = metadata(binary);

	if (meta.minor() < reqMinor)
		throw WrongVersionException(binary, reqMinor, meta.minor());

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

const PluginLoader::LoadedPluginsContainer * PluginLoader::loadedPlugins() const
{
	return & m->loadedPlugins;
}

Plugin::Metadata PluginLoader::metadata(const QString & binary) const
{
	QPluginLoader loader(binary);
	return Plugin::Metadata(binary, loader.metaData().value("MetaData").toObject().toVariantMap());
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
