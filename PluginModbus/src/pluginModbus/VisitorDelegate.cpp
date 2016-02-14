#include "VisitorDelegate.hpp"

#include <modbus/Client.hpp>

namespace cutehmi {
namespace pluginModbus {

VisitorDelegate::VisitorDelegate(const base::ProjectModel::Node * node):
	m_node(node)
{
}

void VisitorDelegate::visit(QMLContextPropertyProxy & proxy)
{
	modbus::Client * client = qobject_cast<modbus::Client *>(m_node->data().object());
	proxy.setContextProperty(m_node->data().name(), client);
}

}
}
