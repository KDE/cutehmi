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

void VisitorDelegate::visit(RunnersRegisterProxy & proxy)
{
	NodeDataObject * dataObject = qobject_cast<NodeDataObject *>(m_node->data().object());
	proxy.add(dataObject->clientRunner());
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
