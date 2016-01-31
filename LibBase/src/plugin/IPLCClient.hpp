#ifndef CUTEHMI_LIBBASE_SRC_PLUGIN_IPLCCLIENTPLUGIN_HPP
#define CUTEHMI_LIBBASE_SRC_PLUGIN_IPLCCLIENTPLUGIN_HPP

#include "../platform.hpp"

#include <QtPlugin>

namespace plugin {

class IPLCClient
{
	public:

	protected:
		virtual ~IPLCClient() = default;

		IPLCClient() = default;
};

}

Q_DECLARE_INTERFACE(plugin::IPLCClient, "CuteHMI.Plugin.IPLCClient")

#endif
