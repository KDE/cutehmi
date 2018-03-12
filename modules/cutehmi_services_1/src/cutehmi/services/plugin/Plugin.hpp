#ifndef H_MODULES_CUTEHMI__SERVICES__1_SRC_CUTEHMI_SERVICES_PLUGIN_PLUGIN_HPP
#define H_MODULES_CUTEHMI__SERVICES__1_SRC_CUTEHMI_SERVICES_PLUGIN_PLUGIN_HPP

#include <cutehmi/IPlugin.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace services {
namespace plugin {

class Plugin:
	public QObject,
	public IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPLUGIN_IID FILE "../../../../cutehmi_services_1.json")
	Q_INTERFACES(cutehmi::IPlugin)

	public:
		void init(ProjectNode & node) override;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
