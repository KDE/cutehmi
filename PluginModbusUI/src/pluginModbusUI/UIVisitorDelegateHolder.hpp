#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATEHOLDER_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATEHOLDER_HPP

#include "UIVisitorDelegate.hpp"

#include <modbus/UIVisitorDelegateHolder.hpp>

#include <base/ProjectModel.hpp>

namespace cutehmi {
namespace pluginModbusUI {

class UIVisitorDelegateHolder:
	public modbus::UIVisitorDelegateHolder
{
	public:
		UIVisitorDelegateHolder(base::ProjectModel::Node & node, QWidget * parentWidget);

		widgets::UIVisitorDelegate * uiDelegate() const override;

	private:
		std::unique_ptr<UIVisitorDelegate> m_uiDelegate;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
