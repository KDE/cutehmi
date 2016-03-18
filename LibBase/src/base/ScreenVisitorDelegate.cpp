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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
