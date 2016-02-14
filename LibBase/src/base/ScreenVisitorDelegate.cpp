#include "ScreenVisitorDelegate.hpp"
#include "ScreenObject.hpp"

namespace cutehmi {
namespace base {

ScreenVisitorDelegate::ScreenVisitorDelegate(const base::ProjectModel::Node * node):
	m_node(node)
{
}

void ScreenVisitorDelegate::visit(QMLVisualComponentProxy & proxy)
{
	ScreenObject * screenObject = qobject_cast<ScreenObject *>(m_node->data().object());
	proxy.loadUrl(QUrl::fromLocalFile(screenObject->source()));
}

}
}
