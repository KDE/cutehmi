#include "ProjectPlugin.hpp"
#include "PluginNodeData.hpp"

#include <QtDebug>

namespace cutehmi {
namespace services {
namespace plugin {

void ProjectPlugin::init(ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> servicesNodeData(new PluginNodeData);
	node.addExtension(servicesNodeData->serviceRegistry());
	node.data().append(std::move(servicesNodeData));
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
