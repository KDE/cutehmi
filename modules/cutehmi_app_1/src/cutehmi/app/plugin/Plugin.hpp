#ifndef H_MODULES_CUTEHMI__APP__1_SRC_CUTEHMI_APP_PLUGIN_PLUGIN_HPP
#define H_MODULES_CUTEHMI__APP__1_SRC_CUTEHMI_APP_PLUGIN_PLUGIN_HPP

#include <cutehmi/xml/IBackendPlugin.hpp>
#include <cutehmi/xml/ParseHelper.hpp>

#include <cutehmi/IPlugin.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace app {
namespace plugin {

class Plugin:
	public QObject,
	public IPlugin,
	public xml::IBackendPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPLUGIN_IID FILE "../../../../cutehmi_app_1.json")
	Q_INTERFACES(cutehmi::IPlugin)

	public:
		// IPlugin
		void init(ProjectNode & node) override;

		// xml::IBackendPlugin
		void readXML(QXmlStreamReader & xmlReader, ProjectNode & node) override;

		// xml::IBackendPlugin
		void writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const override;

	private:
		void parseScreens(const xml::ParseHelper & parentHelper, ProjectNode & node);
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
