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
	if (!Plugin::BinaryExists(binary))
		throw BinaryAbsentException(binary);

	Plugin::Metadata meta = Plugin::BinaryMetadata(binary);

	QList<Plugin::Metadata> metaList{meta};
	int checkMinor = Plugin::CheckReqMinors(reqMinor, metaList);

	if (checkMinor == -1)
		throw BinaryAbsentException(metaList.last().data().value("name").toString());

	if (checkMinor != 0)
		throw WrongVersionException(metaList.last().data().value("name").toString(), checkMinor, metaList.last().minor());

	std::unique_ptr<QPluginLoader> loader(new QPluginLoader(binary));
	if (!plugin(binary)) {
		if (loader->load()) {
			Plugin * plugin = new Plugin(binary, std::move(loader), false, meta);
			CUTEHMI_LOG_DEBUG("Loaded plugin '" << binary << "' version '" << plugin->version() << "'.");
			m->loadedPlugins.append(plugin);

			// Dependant plugins should be implicitly loaded at this point.
			handleImplicitLoads(*plugin);
		} else
			throw FailedLoadException(binary);
	} else
		throw LoadPrecedenceException(binary);
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

void PluginLoader::handleImplicitLoads(const Plugin & plugin) noexcept(false)
{
	QVariantList dependencies = plugin.metadata().value("dependencies").toList();
	for (auto dependency = dependencies.begin(); dependency != dependencies.end(); ++dependency) {
		QString depBinary = Plugin::NameToBinary(dependency->toMap().value("name").toString());
		if (!PluginLoader::plugin(depBinary)) {
			std::unique_ptr<QPluginLoader> depLoader(new QPluginLoader(depBinary));
			Plugin * depPlugin = new Plugin(depBinary, std::move(depLoader), true);
			CUTEHMI_LOG_DEBUG("Plugin '" << depBinary << "' version '" << depPlugin->version() << "' has been implicitly loaded.");
			m->loadedPlugins.append(depPlugin);
			handleImplicitLoads(*depPlugin);
		}
	}
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
