#include "Plugin.hpp"

#include <stupid/Service.hpp>
#include <stupid/NodeDataObject.hpp>
#include <stupid/VisitorDelegate.hpp>

#include <QtDebug>
#include <QSqlDatabase>

namespace cutehmi {
namespace pluginStupid {

base::Error Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectModel::Node & node)
{
	qDebug("CuteHMI.PluginStupid starts parsing its own portion of document...");
	base::ProjectModel::Node * stupidNode = node.addChild(base::ProjectModel::Node::Data("STUPiD"), false);
	while (xmlReader.readNextStartElement()) {
		if (xmlReader.name() == "cutehmi_plugin_stupid") {
			while (xmlReader.readNextStartElement()) {
				if (xmlReader.name() == "client") {
					std::unique_ptr<stupid::Client> client(new stupid::Client);
					QString id = xmlReader.attributes().value("id").toString();
					unsigned long serviceSleep = 0;
					while (xmlReader.readNextStartElement()) {
						if (xmlReader.name() == "session") {
							if (xmlReader.attributes().value("type") == "SQL") {
								while (xmlReader.readNextStartElement()) {
									if (xmlReader.name() == "dbms") {
										std::unique_ptr<stupid::DatabaseConnectionData> dbData(new stupid::DatabaseConnectionData);
										if (xmlReader.attributes().value("name") == "PostgreSQL")
											postgreSQLFromXML(xmlReader, *dbData, id);
										else
											return base::Error::FAIL;	// Unrecognized DBMS.
										client->moveDatabaseConnectionData(std::move(dbData));
									} else
										xmlReader.skipCurrentElement();
								}
							} else
								return base::Error::FAIL;
						} else if (xmlReader.name() == "service") {
							while (xmlReader.readNextStartElement()) {
								if (xmlReader.name() == "sleep") {
									if (xmlReader.readNext() != QXmlStreamReader::Characters)
										return base::Error::FAIL;
									bool ok;
									serviceSleep = xmlReader.text().toULong(& ok);
									if (!ok)
										return base::Error::FAIL;
								}
								xmlReader.skipCurrentElement();	// None of the child elements uses readNextStartElement(). Either readNextStartElement() or skipCurrentElement() must be called for each tag.
							}
						} else
							xmlReader.skipCurrentElement();
					}
					std::unique_ptr<stupid::Service> service(new stupid::Service(QStringLiteral("CuteHMI STUPiD (") + id + ")", client.get()));
					service->setSleep(serviceSleep);
					std::unique_ptr<stupid::NodeDataObject> dataObject(new stupid::NodeDataObject(std::move(client), std::move(service)));
					base::ProjectModel::Node * clientNode = stupidNode->addChild(base::ProjectModel::Node::Data(id, std::move(dataObject)));
					clientNode->setVisitorDelegate(std::unique_ptr<base::ProjectModel::Node::VisitorDelegate>(new stupid::VisitorDelegate(clientNode)));
				} else
					xmlReader.skipCurrentElement();
			}
		} else
			xmlReader.skipCurrentElement();
	}
	return base::Error::OK;
}

base::Error Plugin::writeXML(QXmlStreamWriter & xmlWriter) const
{
	Q_UNUSED(xmlWriter);
	return base::Error::FAIL;
}

base::Error Plugin::postgreSQLFromXML(QXmlStreamReader & xmlReader, stupid::DatabaseConnectionData & dbData, const QString & connectionName)
{
	dbData.type = "QPSQL";
	dbData.connectionName = connectionName;
//	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);
	while (xmlReader.readNextStartElement()) {
		if (xmlReader.name() == "postgresql") {
			while (xmlReader.readNextStartElement()) {
				if (xmlReader.name() == "host") {
					if (xmlReader.readNext() != QXmlStreamReader::Characters)
						return base::Error::FAIL;
					dbData.hostName = xmlReader.text().toString();
//					db.setHostName(xmlReader.text().toString());
				} else if (xmlReader.name() == "port") {
					if (xmlReader.readNext() != QXmlStreamReader::Characters)
						return base::Error::FAIL;
					bool ok;
					int port = xmlReader.text().toInt(& ok);
					if (!ok)
						return base::Error::FAIL;
					dbData.port = port;
//					db.setPort(port);
				} else if (xmlReader.name() == "name") {
					if (xmlReader.readNext() != QXmlStreamReader::Characters)
						return base::Error::FAIL;
					dbData.databaseName = xmlReader.text().toString();
//					db.setDatabaseName(xmlReader.text().toString());
				} else if (xmlReader.name() == "user") {
					if (xmlReader.readNext() != QXmlStreamReader::Characters)
						return base::Error::FAIL;
					dbData.userName = xmlReader.text().toString();
//					db.setUserName(xmlReader.text().toString());
				} else if (xmlReader.name() == "password") {
					if (xmlReader.readNext() != QXmlStreamReader::Characters)
						return base::Error::FAIL;
					dbData.password = xmlReader.text().toString();
//					db.setPassword(xmlReader.text().toString());
				} else
					return base::Error::FAIL;
				xmlReader.skipCurrentElement();
			}
		} else
			xmlReader.skipCurrentElement();
	}
	return base::Error::OK;
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
