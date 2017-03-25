#ifndef STUPIDPLUGINNODEDATA_HPP
#define STUPIDPLUGINNODEDATA_HPP

#include <base/DataBlock.hpp>
#include <base/XMLBackendPlugin.hpp>

namespace cutehmi {
namespace stupid {
namespace plugin {

class PluginNodeData:
	public base::DataBlock
{
	public:
		PluginNodeData(base::IXMLBackendPlugin * implementation);

		base::XMLBackendPlugin * xmlBackendPlugin() const;

	private:
		std::unique_ptr<base::XMLBackendPlugin> m_xmlBackendPlugin;
};

}
}
}

#endif // STUPIDPLUGINNODEDATA_HPP
