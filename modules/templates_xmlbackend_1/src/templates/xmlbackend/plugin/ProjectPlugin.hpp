#ifndef H_MODULES_TEMPLATES__XMLBACKEND__1_SRC_TEMPLATES_XMLBACKEND_PLUGIN_PROJECTPLUGIN_HPP    // Edit! Modify include guards.
#define H_MODULES_TEMPLATES__XMLBACKEND__1_SRC_TEMPLATES_XMLBACKEND_PLUGIN_PROJECTPLUGIN_HPP    // Edit! Modify include guards.

#include "../../../../include/templates/xmlbackend/internal/common.hpp"

#include <cutehmi/IProjectPlugin.hpp>

#include <cutehmi/xml/BackendPlugin.hpp>

#include <QObject>

#include <memory>

namespace templates {       // Edit! Replace 'templates' with custom vendor id.
namespace xmlbackend {      // Edit! Replace 'xmlbackend' with custom module id.
namespace plugin {

/**
 * Project plugin.
 */
class ProjectPlugin:
	public QObject,
	public cutehmi::IProjectPlugin,
	public cutehmi::xml::IBackendPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPROJECTPLUGIN_IID FILE "../../../../cutehmi.metadata.json")
	Q_INTERFACES(cutehmi::IProjectPlugin)

	public:
		/**
		 * Initialize plugin.
		 * @param node node of the plugin.
		 */
		void init(cutehmi::ProjectNode & node) override;

		/**
		 * Read XML.
		 * @param xmlReader XML reader.
		 * @param node plugin node.
		 */
		void readXML(QXmlStreamReader & xmlReader, cutehmi::ProjectNode & node) override;

		/**
		 * Write XML.
		 * @param xmlWriter XML writer.
		 * @param node plugin node.
		 */
		void writeXML(QXmlStreamWriter & xmlWriter, cutehmi::ProjectNode & node) const noexcept(false) override;

	private:
//		void parseXMLBackend(const xml::ParseHelper & parentHelper, ProjectNode & node, const QString & id, const QString & name);

};

}
}
}

#endif
