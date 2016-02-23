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
