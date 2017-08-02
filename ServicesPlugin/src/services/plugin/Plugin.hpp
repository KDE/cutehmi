#ifndef CUTEHMI_SERVICESPLUGIN_SRC_SERVICES_PLUGIN_PLUGIN_HPP
#define CUTEHMI_SERVICESPLUGIN_SRC_SERVICES_PLUGIN_PLUGIN_HPP

#include <base/IPlugin.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace services {
namespace plugin {

class Plugin:
	public QObject,
	public base::IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_BASE_IPLUGIN_IID FILE "ServicesPlugin.json")
	Q_INTERFACES(cutehmi::base::IPlugin)

	public:
		void init(base::ProjectNode & node) override;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
