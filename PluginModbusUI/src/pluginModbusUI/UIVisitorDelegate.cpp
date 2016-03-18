#include "UIVisitorDelegate.hpp"

#include <modbus/Client.hpp>
#include <modbus/NodeDataObject.hpp>

#include <QMenu>

namespace cutehmi {
namespace pluginModbusUI {

UIVisitorDelegate::UIVisitorDelegate(base::ProjectModel::Node & node, QWidget * parentWidget):
	m_errorBox(new widgets::ErrorBox)
{
	modbus::NodeDataObject * dataObject = qobject_cast<modbus::NodeDataObject *>(node.data().object());
	Q_ASSERT(dataObject != nullptr);

	m_clientControlWidget = new ClientControlWidget(dataObject->client(), node.data().name(), parentWidget);
	QObject::connect(dataObject->client(), & modbus::Client::destroyed, m_clientControlWidget, & ClientControlWidget::deleteLater);

	m_errorBox->setTitle(m_clientControlWidget->windowTitle());
	QObject::connect(dataObject->client(), & modbus::Client::error, m_errorBox.get(), & widgets::ErrorBox::execInfo);
}

void UIVisitorDelegate::visit(widgets::UIVisitorDelegate::ContextMenuProxy & proxy)
{
	std::unique_ptr<QMenu> menu(new QMenu);
	QAction * controlWidgetAct = new QAction(tr("Control..."), menu.get());
	QObject::connect(controlWidgetAct, & QAction::triggered, m_clientControlWidget, & ClientControlWidget::showAndActivate);
	menu->addAction(controlWidgetAct);
	proxy.pass(std::move(menu));
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
