#ifndef CUTEHMI_CUTEHMI__APP__1_SRC_APP_PLUGIN_SCREENSNODEDATA_HPP
#define CUTEHMI_CUTEHMI__APP__1_SRC_APP_PLUGIN_SCREENSNODEDATA_HPP

#include "../../../../include/cutehmi/app/MainScreen.hpp"

#include <cutehmi/DataBlock.hpp>

#include <memory>

namespace cutehmi {
namespace app {
namespace plugin {

class ScreensNodeData:
	public DataBlock
{
	public:
		ScreensNodeData(std::unique_ptr<MainScreen> mainScreen);

		MainScreen * mainScreen() const;

	private:
		std::unique_ptr<MainScreen> m_mainScreen;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
