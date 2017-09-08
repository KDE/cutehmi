#ifndef CUTEHMI_CUTEHMI__SCREENLOCK__1_SRC_SCREENLOCK_PLUGIN_PLUGIN_HPP
#define CUTEHMI_CUTEHMI__SCREENLOCK__1_SRC_SCREENLOCK_PLUGIN_PLUGIN_HPP

#include <base/IPlugin.hpp>
#include <base/IXMLBackendPlugin.hpp>
#include <base/xml/ParseHelper.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace screenlock {
namespace plugin {

class Plugin:
	public QObject,
	public base::IPlugin,
	public base::IXMLBackendPlugin
{
	Q_OBJECT
    Q_PLUGIN_METADATA(IID CUTEHMI_BASE_IPLUGIN_IID FILE "cutehmi_screenlock_1.json")
	Q_INTERFACES(cutehmi::base::IPlugin)

	public:
		// base::IPlugin
		void init(base::ProjectNode & node) override;

		// base::IXMLBackendPlugin
		void readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node) override;

		// base::IXMLBackendPlugin
		void writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const override;

	private:
		void parseSSHServer(const base::xml::ParseHelper & parentHelper, base::ProjectNode & node);
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
