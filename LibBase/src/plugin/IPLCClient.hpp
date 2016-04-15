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
		virtual ~IPLCClient() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IPLCClient() = default;
};

}
}

Q_DECLARE_INTERFACE(cutehmi::plugin::IPLCClient, "CuteHMI.Plugin.IPLCClient")

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
