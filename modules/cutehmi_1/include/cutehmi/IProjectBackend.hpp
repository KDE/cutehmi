#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPROJECTBACKEND_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPROJECTBACKEND_HPP

#include "ProjectNode.hpp"
#include "ProjectPluginLoader.hpp"

namespace cutehmi {

/**
 * %Project backend interface.
 */
class CUTEHMI_API IProjectBackend
{
	public:
		virtual void load(const ProjectPluginLoader & pluginLoader, ProjectNode & rootNode) noexcept(false) = 0;

	protected:
		virtual ~IProjectBackend() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IProjectBackend() = default;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
