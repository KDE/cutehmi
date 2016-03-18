#ifndef CUTEHMI_LIBBASE_SRC_BASE_IPROJECTMODELVISITOR_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_IPROJECTMODELVISITOR_HPP

#include "../platform.hpp"
#include "../base/ProjectModel.hpp"

#include <QtPlugin>

namespace cutehmi {
namespace base {

/**
 * Project model visitor interface.
 */
class IProjectModelVisitor
{
	public:
		virtual void visit(base::ProjectModel::Node & node) = 0;

	protected:
		virtual ~IProjectModelVisitor() = default;

		IProjectModelVisitor() = default;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
