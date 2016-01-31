#ifndef XMLPROJECTBACKEND_H
#define XMLPROJECTBACKEND_H

#include "../platform.hpp"
#include "Error.hpp"
#include "PluginLoader.hpp"
#include "ProjectModel.hpp"

#include <QXmlStreamReader>

namespace base {

class CUTEHMI_BASE_API XMLProjectBackend
{
	public:
		struct CUTEHMI_BASE_API Error:
			public base::Error
		{
			enum : int {
				NOT_CUTEHMI_PROJECT_FILE = base::Error::SUBCLASS_BEGIN,
				UNSUPPORTED_VERSION,
				INVALID_FORMAT,
				PLUGIN_NOT_LOADED,
				PLUGIN_WRONG_INTERFACE,
				PLUGIN_PARSE_PROBLEM
			};

			using base::Error::Error;

			QString str() const;
		};

		/**
		 * Constructor.
		 * @param model project model.
		 * @param pluginLoader properly configured plugin loader.
		 */
		XMLProjectBackend(ProjectModel * model, PluginLoader * pluginLoader);

		Error load(QIODevice & device);

//		void save(QIODevice * device);

	private:
		struct Loader0 {
			Loader0(QXmlStreamReader * xmlReader, ProjectModel::Node * root, PluginLoader * pluginLoader);

			Error parse(int versionMinor);

			Error plcClients();

			Error screens();

			private:
				QXmlStreamReader * m_xml;
				ProjectModel::Node * m_root;
				PluginLoader * m_pluginLoader;
		};

//		struct Saver0 {
//		};

		ProjectModel * m_model;
		PluginLoader * m_pluginLoader;
		QXmlStreamReader m_xmlReader;
};

}

#endif // XMLPROJECTBACKEND_H
