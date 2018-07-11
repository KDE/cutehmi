#include "ProjectPlugin.hpp"
#include "PluginNodeData.hpp"
#include "AuthSSHNodeData.hpp"

#include "../../../../include/cutehmi/authssh/logging.hpp"
#include "../../../../include/cutehmi/authssh/Client.hpp"
#include "../../../../include/cutehmi/authssh/ForwardChannel.hpp"

#include <cutehmi/xml/BackendPlugin.hpp>
#include <cutehmi/xml/conversions.hpp>

#include <cutehmi/Exception.hpp>

#include <QtDebug>

#include <vector>

namespace cutehmi {
namespace authssh {
namespace plugin {

void ProjectPlugin::init(ProjectNode & node)
{
    std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
    node.addExtension(pluginNodeData->xmlBackendPlugin());
    node.data().append(std::move(pluginNodeData));
}

void ProjectPlugin::readXML(QXmlStreamReader & xmlReader, ProjectNode & node)
{
	CUTEHMI_LOG_DEBUG("Plugin 'cutehmi_authssh_1' starts parsing its own portion of document...");

    QStringList supportedVersions;
    supportedVersions << "http://michpolicht.github.io/CuteHMI/cutehmi_authssh_1/xsd/1.0/";

    xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << xml::ParseElement("cutehmi_authssh_1", 1, 1);

	const QXmlStreamReader & reader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "cutehmi_authssh_1") {
            xml::ParseHelper nodeHelper(& helper);
			nodeHelper << xml::ParseElement("client", { xml::ParseAttribute("id"), xml::ParseAttribute("name") }, 1, 1);
            while (nodeHelper.readNextRecognizedElement()) {
				if (reader.name() == "client")
					parseClient(nodeHelper, node, reader.attributes().value("id").toString(), reader.attributes().value("name").toString());
            }
        }
    }
}

void ProjectPlugin::writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const noexcept(false)
{
    Q_UNUSED(xmlWriter);
    Q_UNUSED(node);
    throw Exception("cutehmi::authssh::plugin::Plugin::writeXML() not implemented yet.");
}

void ProjectPlugin::parseClient(const xml::ParseHelper & parentHelper, ProjectNode & node, const QString & id, const QString & name)
{
	std::vector<std::unique_ptr<AbstractChannel>> channels;
	std::unique_ptr<Client> client;
	QString host;
	uint port = 0;

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("server_host", 1, 1)
		   << xml::ParseElement("server_port", 1, 1)
		   << xml::ParseElement("channels", 1, 1);

	const QXmlStreamReader & reader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "server_host")
			host = helper.readElementText();
		else if (reader.name() == "server_port") {
			bool ok;
			port = helper.readElementText().toUInt(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'port' element contents to unsigned integer."));
		} else if (reader.name() == "channels")
			parseChannels(helper, channels);
	}

	if (!reader.hasError()) {
		client.reset(new Client);
		client->setServerHost(host);
		client->setServerPort(port);
		for (auto it = channels.begin(); it != channels.end(); ++it)
			client->addChannel(std::move(*it));

		ProjectNode * authsshNode = node.addChild(id, ProjectNodeData(name));
		authsshNode->addExtension(client.get());

		authsshNode->data().append(std::unique_ptr<AuthSSHNodeData>(new AuthSSHNodeData(std::move(client))));
	}
}

void ProjectPlugin::parseChannels(const xml::ParseHelper & parentHelper, std::vector<std::unique_ptr<AbstractChannel>> & channels)
{
	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("channel", { xml::ParseAttribute("type", "forward")}, 0, -1);

	const QXmlStreamReader & reader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "channel") {
			std::unique_ptr<AbstractChannel> channel;
			if (reader.attributes().value("type") == "forward")
				parseForwardChannel(parentHelper, channel);
			channels.push_back(std::move(channel));
		}
	}
}

void ProjectPlugin::parseForwardChannel(const xml::ParseHelper & parentHelper, std::unique_ptr<AbstractChannel> & channel)
{
	QHostAddress remoteHost;
	uint remotePort = 0;
	QHostAddress sourceHost;
	uint localPort = 0;

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("remote_host", 1, 1)
		   << xml::ParseElement("remote_port", 1, 1)
		   << xml::ParseElement("source_host", 1, 1)
		   << xml::ParseElement("local_port", 1, 1);

	const QXmlStreamReader & reader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (reader.name() == "remote_host") {
			remoteHost.setAddress(helper.readElementText());
		} else if (reader.name() == "remote_port") {
			bool ok;
			remotePort = helper.readElementText().toUInt(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'remote_port' element contents to unsigned integer."));
		} else if (reader.name() == "source_host") {
			sourceHost.setAddress(helper.readElementText());
		} else if (reader.name() == "local_port") {
			bool ok;
			localPort = helper.readElementText().toUInt(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'local_port' element contents to unsigned integer."));
		}
	}

	channel.reset(new ForwardChannel(remoteHost, remotePort, sourceHost, localPort));
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
