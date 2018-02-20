#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PLUGINLOADER_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PLUGINLOADER_HPP

#include "internal/common.hpp"
#include "Error.hpp"
#include "ExceptionMixin.hpp"
#include "Plugin.hpp"

#include <QPluginLoader>

#include <memory>

namespace cutehmi {
namespace base {

/**
 * %Plugin loader.
 */
class CUTEHMI_API PluginLoader:
	public QObject
{
	Q_OBJECT

	public:
		class CUTEHMI_API Exception:
			public base::ExceptionMixin<Exception>
		{
			typedef base::ExceptionMixin<Exception> Parent;

			public:
				using Parent::Parent;
		};

		class CUTEHMI_API WrongVersionException:
			public Exception
		{
			public:
				WrongVersionException(const QString & binary, int reqMinor, int minor):
					Exception(tr("Plugin '%1' does not satisfy version requirements. Minor '%2' is available. Minor '%3' or higher is required.").arg(binary).arg(minor).arg(reqMinor))
				{
				}
		};

		class CUTEHMI_API FailedLoadException:
			public Exception
		{
			public:
				FailedLoadException(const QString & binary):
					Exception(tr("Failed to load '%1' plugin.").arg(binary))
				{
				}
		};

		typedef QVector<Plugin *> LoadedPluginsContainer;

		PluginLoader();

		/**
		 * Constructor.
		 * @param pluginsDir plugins directory. Directory will be added to library search paths.
		 */
		explicit PluginLoader(const QString & pluginsDir);

		~PluginLoader() override;

		/**
		 * Set plugins directory.
		 * @param pluginsDir plugins directory. Directory will be added to library search paths.
		 */
		void setPluginsDir(const QString & pluginsDir);

		/**
		 * Load plugin.
		 * @param binary name of plugin binary.
		 * @param minor minimal required minor version.
		 * @return plugin object or @p nullptr if plugin has not been loaded.
		 *
		 * @throws WrongVersionException
		 * @throws FailedLoadException
		 */
		Plugin * loadPlugin(const QString & binary, int reqMinor);

		void unloadPlugins();

		/**
		 * Get plugin.
		 * @param binary name of plugin binary.
		 * @return plugin object or @p nullptr if plugin has not been loaded.
		 */
		Plugin * plugin(const QString & binary);

		Plugin::MetaData metaData(const QString & binary) const;

	private:
		struct Members
		{
			QString pluginsDir;
			mutable QPluginLoader loader;
			LoadedPluginsContainer loadedPlugins;

			Members(const QString & p_pluginsDir = QString()):
				pluginsDir(p_pluginsDir)
			{
			}
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
