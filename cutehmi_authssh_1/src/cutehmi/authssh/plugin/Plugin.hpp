#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1_SRC_AUTHSSH_PLUGIN_PLUGIN_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1_SRC_AUTHSSH_PLUGIN_PLUGIN_HPP

#include "../../../../include/cutehmi/authssh/AbstractChannel.hpp"

#include <cutehmi/xml/IBackendPlugin.hpp>
#include <cutehmi/xml/ParseHelper.hpp>

#include <cutehmi/IPlugin.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace authssh {
namespace plugin {

class Plugin:
	public QObject,
	public IPlugin,
	public xml::IBackendPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPLUGIN_IID FILE "cutehmi_authssh_1.json")
	Q_INTERFACES(cutehmi::IPlugin)

	public:
		// IPlugin
		void init(ProjectNode & node) override;

		// xml::IBackendPlugin
		void readXML(QXmlStreamReader & xmlReader, ProjectNode & node) override;

		// xml::IBackendPlugin
		void writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const override;

	private:
		void parseClient(const xml::ParseHelper & parentHelper, ProjectNode & node, const QString & id, const QString & name);

		void parseChannels(const xml::ParseHelper & parentHelper, std::vector<std::unique_ptr<AbstractChannel> > & channels);

		void parseForwardChannel(const xml::ParseHelper & parentHelper, std::unique_ptr<AbstractChannel> & channel);
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
