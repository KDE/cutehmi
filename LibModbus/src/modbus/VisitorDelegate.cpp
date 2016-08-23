#include "VisitorDelegate.hpp"
#include "NodeDataObject.hpp"

namespace cutehmi {
namespace modbus {

VisitorDelegate::VisitorDelegate(const base::ProjectModel::Node * node):
	m_node(node)
{
}

void VisitorDelegate::visit(QMLContextPropertyProxy & proxy)
{
	NodeDataObject * dataObject = qobject_cast<NodeDataObject *>(m_node->data().object());
	proxy.setContextProperty(m_node->data().name(), dataObject->client());
}

void VisitorDelegate::visit(ServicesProxy & proxy)
{
	NodeDataObject * dataObject = qobject_cast<NodeDataObject *>(m_node->data().object());
	proxy.add(dataObject->service());
}

widgets::UIVisitorDelegate * VisitorDelegate::ui()
{
	if (m_uiHolder)
		return m_uiHolder->uiDelegate();
	else
		return nullptr;
}

void VisitorDelegate::setUIVisitorDelegateHolder(std::unique_ptr<UIVisitorDelegateHolder> holder)
{
	m_uiHolder = std::move(holder);
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
