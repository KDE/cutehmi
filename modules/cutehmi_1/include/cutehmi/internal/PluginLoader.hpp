#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_INTERNAL_PLUGINLOADER_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_INTERNAL_PLUGINLOADER_HPP

#include "common.hpp"
#include "../Error.hpp"
#include "../ExceptionMixin.hpp"
#include "../Plugin.hpp"

#include <QPluginLoader>

#include <memory>

namespace cutehmi {
namespace internal {

/**
 * %Plugin loader.
 */
class PluginLoader:
	public QObject
{
	Q_OBJECT

	public:
		class CUTEHMI_API Exception:
			public ExceptionMixin<Exception>
		{
			typedef ExceptionMixin<Exception> Parent;

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

		explicit PluginLoader(QObject * parent = 0);

		~PluginLoader() override;

		/**
		 * Load plugin.
		 * @param binary name of plugin binary.
		 * @param minor minimal required minor version.
		 * @return plugin object or @p nullptr if plugin has not been loaded.
		 *
		 * @throws WrongVersionException
		 * @throws FailedLoadException
		 */
		Plugin * loadPlugin(const QString & binary, int reqMinor) noexcept(false);

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
			mutable QPluginLoader loader;
			LoadedPluginsContainer loadedPlugins;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
