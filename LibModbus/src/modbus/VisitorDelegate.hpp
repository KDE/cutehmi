#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_VISITORDELEGATE_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_VISITORDELEGATE_HPP

#include "../platform.hpp"
#include "UIVisitorDelegateHolder.hpp"

#include <base/ProjectModel.hpp>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API VisitorDelegate:
	public base::ProjectModel::Node::VisitorDelegate
{
	public:
		VisitorDelegate(const base::ProjectModel::Node * node);

		void visit(QMLContextPropertyProxy & proxy) override;

		void visit(RunnersRegisterProxy & proxy) override;

		widgets::UIVisitorDelegate * ui() override;

		void setUIVisitorDelegateHolder(std::unique_ptr<UIVisitorDelegateHolder> holder);

	private:
		const base::ProjectModel::Node * m_node;
		std::unique_ptr<UIVisitorDelegateHolder> m_uiHolder;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
