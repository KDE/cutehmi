#ifndef CUTEHMI_LIBBASE_SRC_BASE_SCREENVISITORDELEGATE_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SCREENVISITORDELEGATE_HPP

#include "ProjectModel.hpp"

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API ScreenVisitorDelegate:
	public ProjectModel::Node::VisitorDelegate
{
	public:
		ScreenVisitorDelegate(const base::ProjectModel::Node * node);

		void visit(QMLVisualComponentProxy & proxy) override;

	private:
		const base::ProjectModel::Node * m_node;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
