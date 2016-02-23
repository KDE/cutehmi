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
