#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATE_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATE_HPP

#include "ClientControlWidget.hpp"

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
		UIVisitorDelegate(QWidget * parentWidget, modbus::Client * client, const QString & clientName);

		void visit(widgets::UIVisitorDelegate::ContextMenuProxy & proxy) override;

	private:
		modbus::Client * m_client;
		ClientControlWidget * m_clientControlWidget;
		std::unique_ptr<widgets::ErrorBox> m_errorBox;
};

}
}

#endif
