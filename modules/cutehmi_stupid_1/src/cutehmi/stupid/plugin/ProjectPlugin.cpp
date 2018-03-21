#include "ProjectPlugin.hpp"
#include "StupidNodeData.hpp"
#include "PluginNodeData.hpp"
#include "../../../../include/cutehmi/stupid/logging.hpp"
#include "../../../../include/cutehmi/stupid/Service.hpp"

#include <cutehmi/services/ServiceRegistry.hpp>

#include <cutehmi/xml/BackendPlugin.hpp>

#include <cutehmi/Exception.hpp>

#include <QtDebug>
#include <QSqlDatabase>
#include <QQmlContext>

namespace cutehmi {
namespace stupid {
namespace plugin {

void ProjectPlugin::init(ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.registerExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void ProjectPlugin::readXML(QXmlStreamReader & xmlReader, ProjectNode & node)
{
	CUTEHMI_LOG_DEBUG("Plugin 'cutehmi_stupid_1' starts parsing its own portion of document...");

	QStringList supportedVersions;
	supportedVersions << "http://michpolicht.github.io/CuteHMI/cutehmi_stupid_1/xsd/1.0/";

	xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << xml::ParseElement("cutehmi_stupid_1", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_stupid_1") {
			xml::ParseHelper nodeHelper(& helper);
			nodeHelper << xml::ParseElement("stupid", {xml::ParseAttribute("id"),
													   xml::ParseAttribute("name")}, 0);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "stupid")
					parseStupid(nodeHelper, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
			}
		}
	}
}

void ProjectPlugin::writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const noexcept(false)
{
	Q_UNUSED(xmlWriter);
	Q_UNUSED(node);
	throw Exception("cutehmi::stupid::plugin::Plugin::writeXML() not implemented yet.");
}

void ProjectPlugin::parseStupid(const xml::ParseHelper & parentHelper, ProjectNode & node, const QString & id, const QString & name)
{
	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("client", 1, 1)
		   << xml::ParseElement("service", 1, 1);

	std::unique_ptr<Client> client;
	std::unique_ptr<Service> service;
	std::unique_ptr<DatabaseConnectionData> dbData;
	unsigned long serviceSleep = 0;

	const QXmlStreamReader & xmlReader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "client") {
			xml::ParseHelper clientHelper(& helper);
			clientHelper << xml::ParseElement("session", {xml::ParseAttribute("type", "SQL")}, 1, 1);

			while (clientHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "session") {
					xml::ParseHelper sessionHelper(& clientHelper);
					sessionHelper << xml::ParseElement("dbms", {xml::ParseAttribute("name", "PostgreSQL")}, 1, 1);
					while (sessionHelper.readNextRecognizedElement()) {
						if (xmlReader.name() == "dbms") {
							dbData.reset(new DatabaseConnectionData);
							dbData->connectionName = id;
							if (xmlReader.attributes().value("name") == "PostgreSQL") {
								dbData->type = "QPSQL";
								parsePostgreSQL(sessionHelper, *dbData);
							}
						}
					}
				}
			}
		} else if (xmlReader.name() == "service") {
			xml::ParseHelper serviceHelper(& helper);
			serviceHelper << xml::ParseElement("sleep", 1, 1);

			while (serviceHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "sleep") {
					bool ok;
					serviceSleep = serviceHelper.readElementText().toULong(& ok);
					if (!ok)
						serviceHelper.raiseError(QObject::tr("Could not convert 'sleep' element data to long integer."));
				}
			}
		}
	}

	if (!xmlReader.hasError()) {
		client.reset(new Client);
		client->moveDatabaseConnectionData(std::move(dbData));

		service.reset(new Service(name, client.get()));
		service->setSleep(serviceSleep);

		ProjectNode * stupidNode = node.appendChild(id, ProjectNodeData(name));
		stupidNode->registerExtension(client.get());
		stupidNode->registerExtension(service.get());

		if (node.root()->child("cutehmi_services_1")) {
			services::ServiceRegistry * serviceRegistry = qobject_cast<services::ServiceRegistry *>(node.root()->child("cutehmi_services_1")->extension(services::ServiceRegistry::staticMetaObject.className()));
			CUTEHMI_ASSERT(serviceRegistry != nullptr, "pointer must not be nullptr");
			serviceRegistry->add(service.get());
		} else
			CUTEHMI_LOG_WARNING("Plugin 'cutehmi_services_1' not available.");

		stupidNode->data().append(std::unique_ptr<StupidNodeData>(new StupidNodeData(std::move(client), std::move(service))));
	}
}

void ProjectPlugin::parsePostgreSQL(const xml::ParseHelper & parentHelper, DatabaseConnectionData & dbData)
{
	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("postgresql", 1, 1);

	const QXmlStreamReader & xmlReader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "postgresql") {
			xml::ParseHelper postgresqlHelper(& helper);
			postgresqlHelper << xml::ParseElement("port", 1, 1)
							 << xml::ParseElement("host", 1, 1)
							 << xml::ParseElement("name", 1, 1)
							 << xml::ParseElement("user", 1, 1)
							 << xml::ParseElement("password", 1, 1);

			while (postgresqlHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "host")
					dbData.hostName = helper.readElementText();
				else if (xmlReader.name() == "port") {
					bool ok;
					int port = helper.readElementText().toInt(& ok);
					if (!ok)
						helper.raiseError(QObject::tr("Could not convert 'port' data to integer."));
					dbData.port = port;
				} else if (xmlReader.name() == "name")
					dbData.databaseName = helper.readElementText();
				else if (xmlReader.name() == "user")
					dbData.userName = helper.readElementText();
				else if (xmlReader.name() == "password")
					dbData.password = helper.readElementText();
			}
		}
	}
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
