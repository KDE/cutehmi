#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATE_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_UIVISITORDELEGATE_HPP

#include "ClientControlWidget.hpp"

#include <base/ProjectModel.hpp>

#include <QCoreApplication>

namespace pluginModbusGUI {

class GUIVisitorDelegate:
	public base::ProjectModel::Node::GUIVisitorDelegate
{
	Q_DECLARE_TR_FUNCTIONS(pluginModbusUI::UIVisitorDelegate)

	public:
		GUIVisitorDelegate(modbus::Client * client, const QString & clientName);

		void visit(base::ProjectModel::Node::GUIVisitorDelegate::ContextMenuProxy & menuProxy);

	private:
		std::unique_ptr<ClientControlWidget> m_clientControlWidget;
};

}

#endif
