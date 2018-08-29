#include "../../../../include/cutehmi/termobot/internal/common.hpp"

#include <cutehmi/Exception.hpp>
#include <cutehmi/services/ServiceRegistry.hpp>

#include "PluginNodeData.hpp"
#include "ProjectPlugin.hpp"
#include "TermobotNodeData.hpp"
#include "../DatabaseConnectionData.hpp"
#include "../DatabaseThread.hpp"
#include "../../../../include/cutehmi/termobot/ContactsModel.hpp"
#include "../Service.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {

void ProjectPlugin::init(ProjectNode &node)
{
    std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
    node.registerExtension(pluginNodeData->xmlBackendPlugin());
    node.data().append(std::move(pluginNodeData));
}

void ProjectPlugin::readXML(QXmlStreamReader &xmlReader, ProjectNode &node)
{
  CUTEHMI_LOG_DEBUG("Plugin " CUTEHMI_TERMOBOT_NAME " starts parsing its own "
                    "portion of document...");

  QStringList supportedVersions;
  supportedVersions
      << "http://michpolicht.github.io/CuteHMI/cutehmi_termobot_1/xsd/1.0/";

  xml::ParseHelper helper(&xmlReader, supportedVersions);
  helper << xml::ParseElement("cutehmi_termobot_1", 1, 1);

    while (helper.readNextRecognizedElement()) {
      if (xmlReader.name() == "cutehmi_termobot_1") {
        xml::ParseHelper nodeHelper(&helper);
        nodeHelper << xml::ParseElement("termobot", {xml::ParseAttribute("id"), xml::ParseAttribute("name")}, 0);
        while (nodeHelper.readNextRecognizedElement()) {
          if (xmlReader.name() == "termobot")
            parseTermobot(nodeHelper, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
        }
      }
    }
}

void ProjectPlugin::writeXML(QXmlStreamWriter &xmlWriter, ProjectNode &node) const noexcept(false)
{
  Q_UNUSED(xmlWriter);
  Q_UNUSED(node);
  throw Exception(
      "cutehmi::termobot::plugin::Plugin::writeXML() not implemented yet.");
}

void ProjectPlugin::parseTermobot(const xml::ParseHelper &parentHelper, ProjectNode &node, const QString & id, const QString &name)
{
    xml::ParseHelper helper(&parentHelper);
    helper << xml::ParseElement("client", 1, 1);

    std::unique_ptr<DatabaseConnectionData> databaseConnectionData;

    const QXmlStreamReader &xmlReader = helper.xmlReader();
    while (helper.readNextRecognizedElement()) {
      if (xmlReader.name() == "client") {
        xml::ParseHelper clientHelper(&helper);
        clientHelper << xml::ParseElement(
            "session", {xml::ParseAttribute("type", "SQL")}, 1, 1);

        while (clientHelper.readNextRecognizedElement()) {
          if (xmlReader.name() == "session") {
            xml::ParseHelper sessionHelper(&clientHelper);
            sessionHelper << xml::ParseElement(
                "dbms", {xml::ParseAttribute("name", "PostgreSQL")}, 1, 1);
            while (sessionHelper.readNextRecognizedElement()) {
              if (xmlReader.name() == "dbms") {
                  databaseConnectionData.reset(new DatabaseConnectionData);
                  databaseConnectionData->connectionName = id;
				  if (xmlReader.attributes().value("name") == "PostgreSQL") {
					  databaseConnectionData->type = "QPSQL";
					  parsePostgres(sessionHelper, *databaseConnectionData);
				  }
              }
            }
          }
        }
      }
    }

	if (!xmlReader.hasError()) {
		ProjectNode * termobotNode = node.appendChild(id, ProjectNodeData(name));

		std::unique_ptr<DatabaseThread> databaseThread(new DatabaseThread(std::move(databaseConnectionData)));

		std::unique_ptr<Service> service(new Service(name, databaseThread.get()));

		if (node.root()->child("cutehmi_services_1")) {
			services::ServiceRegistry * serviceRegistry = qobject_cast<services::ServiceRegistry *>(node.root()->child("cutehmi_services_1")->extension(services::ServiceRegistry::staticMetaObject.className()));
			CUTEHMI_ASSERT(serviceRegistry != nullptr, "pointer must not be nullptr");
			serviceRegistry->add(service.get());
		} else
			CUTEHMI_LOG_WARNING("Plugin 'cutehmi_services_1' not available.");

		std::unique_ptr<TermobotNodeData> termobotNodeData(new TermobotNodeData(std::move(service), std::move(databaseThread)));
        termobotNode->registerExtension(termobotNodeData->contactsModel());
		termobotNode->registerExtension(termobotNodeData->ds18b20SettingsModel());

        termobotNode->data().append(std::move(termobotNodeData));
    }
}

void ProjectPlugin::parsePostgres(const xml::ParseHelper &parentHelper, DatabaseConnectionData & databaseConnectionData)
{
    xml::ParseHelper helper(&parentHelper);
    helper << xml::ParseElement("postgresql", 1, 1);

    const QXmlStreamReader & xmlReader = helper.xmlReader();
    while (helper.readNextRecognizedElement()) {
        if (xmlReader.name() == "postgresql") {
            xml::ParseHelper postgresqlHelper(&helper);
            postgresqlHelper << xml::ParseElement("host", 1, 1)
                             << xml::ParseElement("port", 1, 1)
                             << xml::ParseElement("name", 1, 1)
                             << xml::ParseElement("user", 1, 1)
                             << xml::ParseElement("password", 1, 1);

            while (postgresqlHelper.readNextRecognizedElement()) {
                if (xmlReader.name() == "host")
                    databaseConnectionData.hostName = helper.readElementText();
                else if (xmlReader.name() == "port") {
                    bool ok;
                    int port =  helper.readElementText().toInt(&ok);
                    if (!ok)
                        helper.raiseError(QObject::tr("Could not convert 'port' data to integer."));
                    databaseConnectionData.port = port;
                }
                else if (xmlReader.name() == "name")
                    databaseConnectionData.databaseName = helper.readElementText();
                else if (xmlReader.name() == "user")
                    databaseConnectionData.userName = helper.readElementText();
                else if (xmlReader.name() == "password")
                    databaseConnectionData.password = helper.readElementText();
            }
        }
    }
}

} // namespace plugin
} // namespace termobot
} // namespace cutehmi

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
