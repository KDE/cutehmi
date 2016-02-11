#include "ScreenVisitorDelegate.hpp"
#include "ScreenObject.hpp"

namespace base {

ScreenVisitorDelegate::ScreenVisitorDelegate(const base::ProjectModel::Node * node):
	m_node(node)
{
}

void ScreenVisitorDelegate::visit(QQmlComponent & component)
{
	ScreenObject * screenObject = qobject_cast<ScreenObject *>(m_node->data().object());
	component.loadUrl(QUrl::fromLocalFile(screenObject->source()));
}

}

