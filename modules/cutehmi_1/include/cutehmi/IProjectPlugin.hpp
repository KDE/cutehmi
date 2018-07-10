#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPROJECTPLUGIN_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPROJECTPLUGIN_HPP

#include "internal/common.hpp"
#include "ProjectNode.hpp"

#include <QtPlugin>

namespace cutehmi {

/**
 * Project plugin interface.
 */
class CUTEHMI_API IProjectPlugin
{
	public:
		virtual void init(ProjectNode & node) = 0;

	protected:
		virtual ~IProjectPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IProjectPlugin() = default;
};

}

#define CUTEHMI_IPROJECTPLUGIN_IID "cutehmi::IProjectPlugin"
Q_DECLARE_INTERFACE(cutehmi::IProjectPlugin, CUTEHMI_IPROJECTPLUGIN_IID)

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
