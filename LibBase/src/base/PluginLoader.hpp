#ifndef CUTEHMI_LIBBASE_SRC_BASE_PLUGINLOADER_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_PLUGINLOADER_HPP

#include "../platform.hpp"
#include "Error.hpp"

#include <QPluginLoader>

namespace cutehmi {
namespace base {

/**
 * Plugin loader.
 */
class CUTEHMI_BASE_API PluginLoader
{
	public:
		struct CUTEHMI_BASE_API Error:
			public base::Error
		{
			enum : int {
				FAIL_LOAD = SUBCLASS_BEGIN,
				WRONG_VERSION
			};

			using base::Error::Error;

			QString str() const;
		};

		PluginLoader();

		/**
		 * Constructor.
		 * @param pluginsDir plugins directory. Directory will be added to library search paths.
		 */
		explicit PluginLoader(const QString & pluginsDir);

		virtual ~PluginLoader();

		/**
		 * Set plugins directory.
		 * @param pluginsDir plugins directory. Directory will be added to library search paths.
		 */
		void setPluginsDir(const QString & pluginsDir);

		void loadPlugins();

		const QStringList & loadedPlugins() const;

		/**
		 * Load plugin.
		 * @param name plugin name.
		 * @param reqVersion required version. Version should be provided in "[major[.minor[.micro]]]" format.
		 * In most cases "micro" numbers can be omitted, because they have no semantics. Omitting a field
		 * is equivalent to setting its value to @p 0.
		 * @return error code.
		 */
		Error loadPlugin(const QString & name, const QString & reqVersion = QString("0.0.0"));

		void unloadPlugins();

		QString pluginVersion(const QString & name);

		/**
		 * Get UI plugin name and version for a specific plugin.
		 * @param name plugin to check.
		 * @param uiName UI plugin name.
		 * @param uiVersion UI plugin version.
		 * @return @p true if UI plugin is specified, @p false otherwise. Additionaly
		 * @a uiName and @a uiVersion are set if function returns @p true.
		 */
		bool uiPlugin(const QString & name, QString & uiName, QString & uiVersion);

		/**
		 * Get root component of a plugin. Plugin should be loaded before calling this function.
		 * @param name plugin name.
		 * @return root component of a plugin or @p nullptr if plugin has not been loaded.
		 */
		QObject * instance(const QString & name);

	private:
		bool checkVersion(const QString & pluginVersion, const QString & reqVersion);

		void parseVersion(const QString & version, int & major, int & minor, int & micro);

	private:
		QPluginLoader m_loader;
		QStringList m_loadedPlugins;
		QString m_pluginsDir;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
