#ifndef CUTEHMI_LIBBASE_SRC_PLUGIN_IPLCCLIENT_HPP
#define CUTEHMI_LIBBASE_SRC_PLUGIN_IPLCCLIENT_HPP

#include "../platform.hpp"

#include <QtPlugin>

namespace cutehmi {
namespace plugin {

/**
 * @todo gather all PLC plugin interfaces into IPLCPlugin.
 *
 * @todo move it to some different namespace.
 */
class IPLCClient
{
	public:

	protected:
		virtual ~IPLCClient() = default;

		IPLCClient() = default;
};

}
}

Q_DECLARE_INTERFACE(cutehmi::plugin::IPLCClient, "CuteHMI.Plugin.IPLCClient")

#endif
