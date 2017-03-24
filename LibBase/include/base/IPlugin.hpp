#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_IPLUGIN_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_IPLUGIN_HPP

#include "internal/common.hpp"
#include "ProjectNode.hpp"

#include <QtPlugin>

namespace cutehmi {
namespace base {

/**
 * Plugin interface.
 */
class IPlugin
{
	public:
		virtual void init(ProjectNode & node) = 0;

	protected:
		virtual ~IPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IPlugin() = default;
};

}
}

#define CUTEHMI_BASE_IPLUGIN_IID "cutehmi::base::IPlugin"
Q_DECLARE_INTERFACE(cutehmi::base::IPlugin, CUTEHMI_BASE_IPLUGIN_IID)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
