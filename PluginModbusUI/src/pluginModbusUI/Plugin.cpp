#include "Plugin.hpp"
#include "VisitorDelegate.hpp"

#include <modbus/Client.hpp>

#include <QtDebug>

#include <memory>

namespace cutehmi {
namespace pluginModbusUI {

QString Plugin::M_ProjectName;

QString Plugin::ProjectName()
{
	return M_ProjectName;
}

Plugin::Plugin():
	m_parentWidget(nullptr)
{
}

void Plugin::setParentWidget(QWidget * widget)
{
	m_parentWidget = widget;
}

void Plugin::visit(base::ProjectModel::Node & node)
{
	if (node.parent() == nullptr)
		M_ProjectName = node.data().name();

	modbus::Client * client = qobject_cast<modbus::Client *>(node.data().object());
	if (client != nullptr)
		node.setVisitorDelegate(std::unique_ptr<VisitorDelegate>(new VisitorDelegate(m_parentWidget, client, node.data().name())));
}

}
}
