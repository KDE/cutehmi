#include "UIVisitorDelegateHolder.hpp"

namespace cutehmi {
namespace pluginModbusUI {

UIVisitorDelegateHolder::UIVisitorDelegateHolder(base::ProjectModel::Node & node, QWidget * parentWidget):
	m_uiDelegate(new UIVisitorDelegate(node, parentWidget))
{
}

widgets::UIVisitorDelegate * UIVisitorDelegateHolder::uiDelegate() const
{
	return m_uiDelegate.get();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
