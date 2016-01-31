#ifndef CUTEHMI_PLUGINLOADER_H
#define CUTEHMI_PLUGINLOADER_H

#include "../platform.hpp"
#include "Error.hpp"

#include <QPluginLoader>

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

		Error loadPlugin(const QString & name, const QString & reqVersion = QString("0.0.0"));

		void unloadPlugins();

		QString pluginVersion(const QString & name);

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

#endif // PLUGINLOADER_H
