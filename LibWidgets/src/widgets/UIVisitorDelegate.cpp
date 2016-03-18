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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
