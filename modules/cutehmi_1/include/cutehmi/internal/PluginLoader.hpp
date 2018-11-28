#ifndef H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_INTERNAL_PLUGINLOADER_HPP
#define H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_INTERNAL_PLUGINLOADER_HPP

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

		class CUTEHMI_API BinaryAbsentException:
			public Exception
		{
			public:
				BinaryAbsentException(const QString & binary):
					Exception(tr("Could not find '%1' plugin binary.").arg(binary))
				{
				}
		};

		class CUTEHMI_API LoadPrecedenceException:
			public Exception
		{
			public:
				LoadPrecedenceException(const QString & binary):
					Exception(tr("Plugin '%1' have been implicitly loaded by dependant plugin, which disqualifies further explicit loading.").arg(binary))
				{
				}
		};

		typedef QVector<Plugin *> LoadedPluginsContainer;

		explicit PluginLoader(QObject * parent = 0);

		~PluginLoader() override;

		/**
		 * Load plugin.
		 * @param binary name of plugin binary.
         * @param reqMinor minimal required minor version.
		 * @return plugin object or @p nullptr if plugin has not been loaded.
		 *
		 * @throws WrongVersionException
		 * @throws FailedLoadException
		 */
		Plugin * loadPlugin(const QString & binary, int reqMinor) noexcept(false);

		void unloadPlugins();

		/**
		 * Get loaded plugin.
		 * @param binary name of plugin binary.
		 * @return plugin object or @p nullptr if plugin has not been loaded.
		 */
		Plugin * plugin(const QString & binary);

		const LoadedPluginsContainer * loadedPlugins() const;

	private:
		void handleImplicitLoads(const Plugin & plugin) noexcept(false);

	private:
		struct Members
		{
			LoadedPluginsContainer loadedPlugins;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
