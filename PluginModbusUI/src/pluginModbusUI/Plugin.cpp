#include "Plugin.hpp"
#include "UIVisitorDelegateHolder.hpp"

#include <modbus/NodeDataObject.hpp>
#include <modbus/VisitorDelegate.hpp>

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

	modbus::NodeDataObject * dataObject = qobject_cast<modbus::NodeDataObject *>(node.data().object());
	if (dataObject != nullptr) {
		modbus::VisitorDelegate * delegate = dynamic_cast<modbus::VisitorDelegate *>(node.visitorDelegate());
		Q_ASSERT(delegate != nullptr);
		delegate->setUIVisitorDelegateHolder(std::unique_ptr<modbus::UIVisitorDelegateHolder>(new UIVisitorDelegateHolder(node, m_parentWidget)));
	}
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
