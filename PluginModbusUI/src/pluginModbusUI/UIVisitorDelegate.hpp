#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATE_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATE_HPP

#include "ClientControlWidget.hpp"

#include <base/ProjectModel.hpp>

#include <widgets/ErrorBox.hpp>
#include <widgets/UIVisitorDelegate.hpp>

#include <QCoreApplication>

namespace cutehmi {

namespace pluginModbusUI {

class UIVisitorDelegate:
	public widgets::UIVisitorDelegate
{
	Q_DECLARE_TR_FUNCTIONS(pluginModbusUI::UIVisitorDelegate)

	public:
		UIVisitorDelegate(base::ProjectModel::Node & node, QWidget * parentWidget);

		void visit(widgets::UIVisitorDelegate::ContextMenuProxy & proxy) override;

	private:
		ClientControlWidget * m_clientControlWidget;
		std::unique_ptr<widgets::ErrorBox> m_errorBox;
};

}
}

#endif
