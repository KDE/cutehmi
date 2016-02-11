#include "GUIVisitorDelegate.hpp"

#include <debug/DestructorTest.hpp>

#include <QMenu>

namespace pluginModbusGUI {

GUIVisitorDelegate::GUIVisitorDelegate(modbus::Client * client, const QString & clientName):
	m_clientControlWidget(new ClientControlWidget(client, clientName))
{
}

void GUIVisitorDelegate::visit(base::ProjectModel::Node::GUIVisitorDelegate::ContextMenuProxy & menuProxy)
{
	QMenu * menu = new QMenu;
	QAction * controlWidgetAct = new QAction(tr("Control..."), menu);
	QObject::connect(controlWidgetAct, & QAction::triggered, m_clientControlWidget.get(), & QWidget::show);
	menu->addAction(controlWidgetAct);
	menuProxy.move(menu);
}

}

