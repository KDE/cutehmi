#include "ProjectPlugin.hpp"
#include "PluginNodeData.hpp"

#include <QtDebug>

namespace templates {        // Edit! Replace 'templates' with custom vendor id.
namespace projectplugin {    // Edit! Replace 'projectplugin' with custom module id.
namespace plugin {

void ProjectPlugin::init(cutehmi::ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData);
	node.data().append(std::move(pluginNodeData));
}

}
}
}
