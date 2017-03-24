#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_INTERNAL_PLUGINNODEDATA_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_INTERNAL_PLUGINNODEDATA_HPP

#include "common.hpp"
#include "../IPlugin.hpp"
#include "../Plugin.hpp"
#include "../DataBlock.hpp"

namespace cutehmi {
namespace base {
namespace internal {

class CUTEHMI_BASE_API PluginNodeData:
	public DataBlock
{
	public:
		PluginNodeData(Plugin * plugin, const QString & minVersion);

		Plugin * plugin() const;

		QString minVersion() const;

		IPlugin * pluginInstance() const;

	private:
		struct Members
		{
			Plugin * plugin;
			QString minVersion;
		};

		std::unique_ptr<Members> m;
};

}
}
}

#endif
