#include "UIVisitorDelegate.hpp"

#include <modbus/Client.hpp>

#include <QMenu>

namespace cutehmi {
namespace pluginModbusUI {

UIVisitorDelegate::UIVisitorDelegate(QWidget * parentWidget, modbus::Client * client, const QString & clientName):
	m_clientControlWidget(new ClientControlWidget(client, clientName, parentWidget)),
	m_errorBox(new widgets::ErrorBox)
{
	m_errorBox->setTitle(m_clientControlWidget->windowTitle());
	QObject::connect(client, & modbus::Client::error, m_errorBox.get(), & widgets::ErrorBox::execInfo);
	QObject::connect(client, & modbus::Client::destroyed, m_clientControlWidget, & ClientControlWidget::deleteLater);
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
