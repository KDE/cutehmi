#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPLUGIN_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPLUGIN_HPP

#include "internal/common.hpp"
#include "ProjectNode.hpp"

#include <QtPlugin>

namespace cutehmi {

/**
 * Plugin interface.
 */
class CUTEHMI_API IPlugin
{
	public:
		virtual void init(ProjectNode & node) = 0;

	protected:
		virtual ~IPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IPlugin() = default;
};

}

#define CUTEHMI_IPLUGIN_IID "cutehmi::IPlugin"
Q_DECLARE_INTERFACE(cutehmi::IPlugin, CUTEHMI_IPLUGIN_IID)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
