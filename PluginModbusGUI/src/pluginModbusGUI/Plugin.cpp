#include "Plugin.hpp"
#include "GUIVisitorDelegate.hpp"

#include <modbus/Client.hpp>

#include <QtDebug>

#include <memory>

namespace pluginModbusGUI {

QString Plugin::M_ProjectName;

QString Plugin::ProjectName()
{
	return M_ProjectName;
}

void Plugin::visit(base::ProjectModel::Node & node)
{
	if (node.parent() == nullptr)
		M_ProjectName = node.data().name();

	modbus::Client * client = qobject_cast<modbus::Client *>(node.data().object());
	if (client != nullptr)
		node.setGUIVisitorDelegate(std::unique_ptr<GUIVisitorDelegate>(new GUIVisitorDelegate(client, node.data().name())));
}

}
