#include "PluginNodeData.hpp"

#include "ProjectPlugin.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {

void ProjectPlugin::init(ProjectNode &node) {
  std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
  node.addExtension(pluginNodeData->xmlBackendPlugin());
  node.data().append(std::move(pluginNodeData));
}

void ProjectPlugin::readXML(QXmlStreamReader &xmlReader, ProjectNode &node) {
  CUTEHMI_LOG_DEBUG("Plugin 'cutehmi_termobot_1' starts parsing its own "
                    "portion of document...");

  QStringList supportedVersions;
  supportedVersions
      << "http://michpolicht.github.io/CuteHMI/cutehmi_termobot_1/xsd/1.0";

  xml::ParserHelper helper(&xmlReader, supportedVersions);
  helper << xml::ParseElement("cutehmi_termobot_1", 1, 1);

  while (helper.readNextRecognizedElement()) {
    if (xmlReader.name() == "cutehmi_termobot_1") {
      xml::ParseHelper nodeHelper(&helper);
      nodeHelper << xml::ParseElement(
          "termobot", {xml::ParseAttribute("id"), xml::ParseAttribute("name")},
          0);
      while (nodeHelper.readNextRecognizedElement()) {
        if (xmlReader.name() == "termobot")
          parseTermobot(nodeHelper, node,
                        xmlReader.attributes().value("id").toString());
      }
    }
  }
}

void ProjectPlugin::writeXML(QXmlStreamWriter &xmlWriter,
                             ProjectNode &node) const noexcept(false) {
  Q_UNUSED(xmlWriter);
  Q_UNUSED(node);
  throw Exception(
      "cutehmi::termobot::plugin::Plugin::writeXML() not implemented yet.");
}

void ProjectPlugin::parseTermobot(const xml::ParseHelper &parentHelper,
                                  ProjectNode &node, const QString &name) {
  xml::ParseHelper helper(&parentHelper);
  helper << xml::ParseElement("client", 1, 1)
         << xml::ParseElement("service", 1, 1);
}

} // namespace plugin
} // namespace termobot
} // namespace cutehmi
