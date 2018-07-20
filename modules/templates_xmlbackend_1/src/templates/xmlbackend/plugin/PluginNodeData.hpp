#ifndef H_MODULES_TEMPLATES__XMLBACKEND__1_SRC_TEMPLATES_XMLBACKEND_PLUGIN_PLUGINNODEDATA_HPP    // Edit! Modify include guards.
#define H_MODULES_TEMPLATES__XMLBACKEND__1_SRC_TEMPLATES_XMLBACKEND_PLUGIN_PLUGINNODEDATA_HPP    // Edit! Modify include guards.

#include <cutehmi/xml/BackendPlugin.hpp>

#include <cutehmi/DataBlock.hpp>

namespace templates {       // Edit! Replace 'templates' with custom vendor id.
namespace xmlbackend {      // Edit! Replace 'xmlbackend' with custom module id.
namespace plugin {

/**
 * Plugin node data.
 */
class PluginNodeData:
	public cutehmi::DataBlock
{
	public:
		/**
		 * Constructor.
		 * @param implementation object implementing
		 * cutehmi::xml::IBackendPlugin interface.
		 */
		PluginNodeData(cutehmi::xml::IBackendPlugin * implementation);

		/**
		 * Get XML backend plugin object.
		 * @return XML backend plugin object.
		 */
		cutehmi::xml::BackendPlugin * xmlBackendPlugin() const;

	private:
		std::unique_ptr<cutehmi::xml::BackendPlugin> m_xmlBackendPlugin;
};

}
}
}

#endif

