#include "ProjectPlugin.hpp"
#include "PluginNodeData.hpp"

#include <cutehmi/xml/BackendPlugin.hpp>
#include <cutehmi/xml/ParseHelper.hpp>

#include <cutehmi/Exception.hpp>

#include <QtDebug>

namespace templates {       // Edit! Replace 'templates' with custom vendor id.
namespace xmlbackend {      // Edit! Replace 'xmlbackend' with custom module id.
namespace plugin {

void ProjectPlugin::init(cutehmi::ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.registerExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void ProjectPlugin::readXML(QXmlStreamReader & xmlReader, cutehmi::ProjectNode & node)
{
	CUTEHMI_LOG_DEBUG("Plugin " TEMPLATES_XMLBACKEND_NAME " starts parsing its own portion of document...");	// Edit! Replace 'TEMPLATES_XMLBACKEND_NAME' with 'VENDOR_MODULE_NAME'.

	QStringList supportedVersions;
	supportedVersions << "http://michpolicht.github.io/CuteHMI/templates_xmlbackend_1/xsd/1.0/";   // Edit! Replace 'templates_xmlbackend_1' with 'vendor_module'.

	cutehmi::xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << cutehmi::xml::ParseElement("templates_xmlbackend_1", 1, 1);    // Edit! Replace 'templates_xmlbackend_1' with 'vendor_module'.

	Q_UNUSED(node);		// Edit! Macro used to kill the warning about unused parameter, which normally would be used by plugin-specific code (commented below).
//	while (helper.readNextRecognizedElement()) {
//		if (xmlReader.name() == "templates_xmlbackend_1") {
//			xml::ParseHelper nodeHelper(& helper);
//			nodeHelper << xml::ParseElement("xmlbackend", {xml::ParseAttribute("id"),
//														   xml::ParseAttribute("name")}, 0);
//			while (nodeHelper.readNextRecognizedElement()) {
//				if (xmlReader.name() == "xmlbackend")
//					parseXMLBackend(nodeHelper, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
//			}
//		}
//	}
}

void ProjectPlugin::writeXML(QXmlStreamWriter & xmlWriter, cutehmi::ProjectNode & node) const noexcept(false)
{
	Q_UNUSED(xmlWriter);
	Q_UNUSED(node);
	throw cutehmi::Exception("cutehmi::xml::IBackendPlugin::writeXML() not implemented yet.");
}

//void ProjectPlugin::parseXMLBackend(const xml::ParseHelper & parentHelper, ProjectNode & node, const QString & id, const QString & name)
//{
//}

}
}
}
