#include "UIVisitorDelegate.hpp"

#include <QWidget>

namespace cutehmi {
namespace widgets {

UIVisitorDelegate::ContextMenuProxy::ContextMenuProxy(std::unique_ptr<QMenu> & menu):
	m_menu(menu)
{
}

void UIVisitorDelegate::ContextMenuProxy::pass(std::unique_ptr<QMenu> menu)
{
	m_menu = std::move(menu);
}

void UIVisitorDelegate::visit(ContextMenuProxy & proxy)
{
	Q_UNUSED(proxy);
}

}
}
