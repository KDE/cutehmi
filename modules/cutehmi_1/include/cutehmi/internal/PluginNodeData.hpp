#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_INTERNAL_PLUGINNODEDATA_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_INTERNAL_PLUGINNODEDATA_HPP

#include "common.hpp"
#include "../DataBlock.hpp"

namespace cutehmi {

class Plugin;
class IPlugin;

namespace internal {

class PluginNodeData:
	public DataBlock
{
	public:
		PluginNodeData(Plugin * plugin, int reqMinor);

		Plugin * plugin() const;

		int reqMinor() const;

		IPlugin * pluginInstance() const;

	private:
		struct Members
		{
			Plugin * plugin;
			int reqMinor;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
