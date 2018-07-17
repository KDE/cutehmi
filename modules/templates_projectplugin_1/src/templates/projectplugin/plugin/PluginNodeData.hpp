#ifndef H_MODULES_TEMPLATES__PROJECTPLUGIN__1_SRC_TEMPLATES_PROJECTPLUGIN_PLUGIN_PLUGINNODEDATA_HPP    // Edit! Modify include guards.
#define H_MODULES_TEMPLATES__PROJECTPLUGIN__1_SRC_TEMPLATES_PROJECTPLUGIN_PLUGIN_PLUGINNODEDATA_HPP    // Edit! Modify include guards.

#include <cutehmi/DataBlock.hpp>

namespace templates {       // Edit! Replace 'templates' with custom vendor id.
namespace projectplugin {   // Edit! Replace 'projectplugin' with custom module id.
namespace plugin {

/**
 * Plugin node data.
 */
class PluginNodeData:
    public cutehmi::DataBlock
{
	public:
        PluginNodeData();   // Edit! Provide custom constructor if necessary.

//		YourData * yourData() const;            // Edit! Provide your own methods as necessary.

    private:
//		std::unique_ptr<YourData> m_yourData;   // Edit! Provide your own members as necessary and initialize them.
};

}
}
}

#endif
