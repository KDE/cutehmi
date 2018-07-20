#ifndef H_MODULES_TEMPLATES__PROJECTPLUGIN__1_SRC_TEMPLATES_PROJECTPLUGIN_PLUGIN_PROJECTPLUGIN_HPP    // Edit! Modify include guards.
#define H_MODULES_TEMPLATES__PROJECTPLUGIN__1_SRC_TEMPLATES_PROJECTPLUGIN_PLUGIN_PROJECTPLUGIN_HPP    // Edit! Modify include guards.

#include "../../../../cutehmi.metadata.hpp"

#include <cutehmi/IProjectPlugin.hpp>

#include <QObject>

#include <memory>

namespace templates {        // Edit! Replace 'templates' with custom vendor id.
namespace projectplugin {    // Edit! Replace 'projectplugin' with custom module id.
namespace plugin {

/**
 * Project plugin.
 */
class ProjectPlugin:
	public QObject,
	public cutehmi::IProjectPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPROJECTPLUGIN_IID FILE "../../../../cutehmi.metadata.json")
	Q_INTERFACES(cutehmi::IProjectPlugin)

	public:
		/**
		 * Initialize plugin.
		 * @param node node of the plugin.
		 */
		void init(cutehmi::ProjectNode & node) override;
};

}
}
}

#endif
