#include "macros.hpp"
#include "Plugin.hpp"
#include "StupidNodeData.hpp"
#include "PluginNodeData.hpp"

#include <stupid/Service.hpp>

#include <services/ServiceRegistry.hpp>

#include <base/XMLBackendPlugin.hpp>
#include <base/Exception.hpp>

#include <QtDebug>
#include <QSqlDatabase>
#include <QQmlContext>

namespace cutehmi {
namespace stupid {
namespace plugin {

void Plugin::init(base::ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.addExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node)
{
	CUTEHMI_STUPID_PLUGIN_QDEBUG("Plugin 'cutehmi_stupid_1' starts parsing its own portion of document...");

	QStringList supportedVersions;
	supportedVersions << "http://michpolicht.github.io/CuteHMI/StupidPlugin/xsd/1.0/";

	base::xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << base::xml::ParseElement("cutehmi_stupid_1", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_stupid_1") {
			base::xml::ParseHelper nodeHelper(& helper);
			nodeHelper << base::xml::ParseElement("stupid", {base::xml::ParseAttribute("id"),
															 base::xml::ParseAttribute("name")}, 0);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "stupid")
					parseStupid(nodeHelper, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
			}
		}
	}
}

void Plugin::writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const
{
	Q_UNUSED(xmlWriter);
	Q_UNUSED(node);
	throw base::Exception("cutehmi::stupid::plugin::Plugin::writeXML() not implemented yet.");
}

void Plugin::parseStupid(const base::xml::ParseHelper & parentHelper, base::ProjectNode & node, const QString & id, const QString & name)
{
	base::xml::ParseHelper helper(& parentHelper);
	helper << base::xml::ParseElement("client", 1, 1)
		   << base::xml::ParseElement("service", 1, 1);

	std::unique_ptr<Client> client;
	std::unique_ptr<Service> service;
	std::unique_ptr<DatabaseConnectionData> dbData;
	unsigned long serviceSleep = 0;

	QXmlStreamReader & xmlReader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "client") {
			base::xml::ParseHelper clientHelper(& helper);
			clientHelper << base::xml::ParseElement("session", {base::xml::ParseAttribute("type", "SQL")}, 1, 1);

			while (clientHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "session") {
					base::xml::ParseHelper sessionHelper(& clientHelper);
					sessionHelper << base::xml::ParseElement("dbms", {base::xml::ParseAttribute("name", "PostgreSQL")}, 1, 1);
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
			base::xml::ParseHelper serviceHelper(& helper);
			serviceHelper << base::xml::ParseElement("sleep", 1, 1);

			while (serviceHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "sleep") {
					bool ok;
					serviceSleep = xmlReader.readElementText().toULong(& ok);
					if (!ok)
						xmlReader.raiseError(QObject::tr("Could not convert 'sleep' element data to long integer."));
				}
			}
		}
	}

	client.reset(new Client);
	client->moveDatabaseConnectionData(std::move(dbData));

	service.reset(new Service(name, client.get()));
	service->setSleep(serviceSleep);

	base::ProjectNode * stupidNode = node.addChild(id, base::ProjectNodeData(name));
	stupidNode->addExtension(client.get());
	stupidNode->addExtension(service.get());

	if (node.root()->child("cutehmi_services_1")) {
		services::ServiceRegistry * serviceRegistry = qobject_cast<services::ServiceRegistry *>(node.root()->child("cutehmi_services_1")->extension(services::ServiceRegistry::staticMetaObject.className()));
		CUTEHMI_BASE_ASSERT(serviceRegistry != nullptr, "pointer must not be nullptr");
		serviceRegistry->add(service.get());
	} else
		CUTEHMI_STUPID_PLUGIN_QWARNING("Plugin 'cutehmi_services_1' not available.");

	stupidNode->data().append(std::unique_ptr<StupidNodeData>(new StupidNodeData(std::move(client), std::move(service))));
}

void Plugin::parsePostgreSQL(const base::xml::ParseHelper & parentHelper, DatabaseConnectionData & dbData)
{
	base::xml::ParseHelper helper(& parentHelper);
	helper << base::xml::ParseElement("postgresql", 1, 1);

	QXmlStreamReader & xmlReader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "postgresql") {
			base::xml::ParseHelper postgresqlHelper(& helper);
			postgresqlHelper << base::xml::ParseElement("port", 1, 1)
							 << base::xml::ParseElement("host", 1, 1)
							 << base::xml::ParseElement("name", 1, 1)
							 << base::xml::ParseElement("user", 1, 1)
							 << base::xml::ParseElement("password", 1, 1);

			while (postgresqlHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "host")
					dbData.hostName = xmlReader.readElementText();
				else if (xmlReader.name() == "port") {
					bool ok;
					int port = xmlReader.readElementText().toInt(& ok);
					if (!ok)
						xmlReader.raiseError(QObject::tr("Could not convert 'port' data to integer."));
					dbData.port = port;
				} else if (xmlReader.name() == "name")
					dbData.databaseName = xmlReader.readElementText();
				else if (xmlReader.name() == "user")
					dbData.userName = xmlReader.readElementText();
				else if (xmlReader.name() == "password")
					dbData.password = xmlReader.readElementText();
			}
		}
	}
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
