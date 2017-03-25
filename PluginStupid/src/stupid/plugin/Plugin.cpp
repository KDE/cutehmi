#include "macros.hpp"
#include "Plugin.hpp"
#include "StupidNodeData.hpp"
#include "PluginNodeData.hpp"

#include <stupid/Service.hpp>
#include <stupid/VisitorDelegate.hpp>

#include <services/ServiceRegistry.hpp>

#include <base/XMLBackendPlugin.hpp>
#include <base/xml/ParseHelper.hpp>
#include <base/Exception.hpp>

#include <QtDebug>
#include <QSqlDatabase>
#include <QQmlContext>

namespace cutehmi {
namespace stupid {
namespace plugin {

constexpr const char * Plugin::NAMESPACE_URI;

void Plugin::init(base::ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.addExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node)
{
	CUTEHMI_STUPID_PLUGIN_QDEBUG("Plugin cutehmi.stupid starts parsing its own portion of document...");

	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("cutehmi_plugin_stupid", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_plugin_stupid") {
			base::xml::ParseHelper nodeHelper(& xmlReader, NAMESPACE_URI);
			nodeHelper << base::xml::ParseElement("stupid", {base::xml::ParseAttribute("id"),
															 base::xml::ParseAttribute("name")}, 0);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "stupid")
					parseStupid(xmlReader, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
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

void Plugin::parseStupid(QXmlStreamReader & xmlReader, base::ProjectNode & node, const QString & id, const QString & name)
{
	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("client", 1, 1)
		   << base::xml::ParseElement("service", 1, 1);

	std::unique_ptr<Client> client;
	std::unique_ptr<Service> service;
	std::unique_ptr<DatabaseConnectionData> dbData;
	unsigned long serviceSleep = 0;

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "client") {
			base::xml::ParseHelper clientHelper(& xmlReader, NAMESPACE_URI);
			clientHelper << base::xml::ParseElement("session", {base::xml::ParseAttribute("type", "SQL")}, 1, 1);

			while (clientHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "session") {
					base::xml::ParseHelper sessionHelper(& xmlReader, NAMESPACE_URI);
					sessionHelper << base::xml::ParseElement("dbms", {base::xml::ParseAttribute("name", "PostgreSQL")}, 1, 1);
					while (sessionHelper.readNextRecognizedElement()) {
						if (xmlReader.name() == "dbms") {
							dbData.reset(new DatabaseConnectionData);
							dbData->connectionName = id;
							if (xmlReader.attributes().value("name") == "PostgreSQL") {
								dbData->type = "QPSQL";
								parsePostgreSQL(xmlReader, *dbData);
							}
						}
					}
				}
			}
		} else if (xmlReader.name() == "service") {
			base::xml::ParseHelper serviceHelper(& xmlReader, NAMESPACE_URI);
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

	base::ProjectNode * stupidNode = node.addChild(id, base::ProjectNode::Data(name));
	stupidNode->addExtension(client.get());
	stupidNode->addExtension(service.get());

	if (node.root()->child("cutehmi.services")) {
		services::ServiceRegistry * serviceRegistry = qobject_cast<services::ServiceRegistry *>(node.root()->child("cutehmi.services")->extension(services::ServiceRegistry::staticMetaObject.className()));
		CUTEHMI_BASE_ASSERT(serviceRegistry != nullptr, "pointer must not be nullptr");
		serviceRegistry->add(service.get());
	} else
		CUTEHMI_STUPID_PLUGIN_QWARNING("Extension 'cutehmi.services' not available.");

	stupidNode->data().append(std::unique_ptr<StupidNodeData>(new StupidNodeData(std::move(client), std::move(service))));
}

void Plugin::parsePostgreSQL(QXmlStreamReader & xmlReader, DatabaseConnectionData & dbData)
{
	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("postgresql", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "postgresql") {
			base::xml::ParseHelper postgresqlHelper(& xmlReader, NAMESPACE_URI);
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
