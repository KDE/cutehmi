#ifndef H_MODULES_CUTEHMI__SERVICES__1_SRC_CUTEHMI_SERVICES_PLUGIN_PROJECTPLUGIN_HPP
#define H_MODULES_CUTEHMI__SERVICES__1_SRC_CUTEHMI_SERVICES_PLUGIN_PROJECTPLUGIN_HPP

#include "../../../../cutehmi.metadata.hpp"

#include <cutehmi/IProjectPlugin.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace services {
namespace plugin {

class ProjectPlugin:
	public QObject,
	public IProjectPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPROJECTPLUGIN_IID FILE "../../../../cutehmi.metadata.json")
	Q_INTERFACES(cutehmi::IProjectPlugin)

	public:
		void init(ProjectNode & node) override;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
