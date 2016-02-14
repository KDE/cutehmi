#include "VisitorDelegate.hpp"

namespace cutehmi {
namespace pluginModbusUI {

VisitorDelegate::VisitorDelegate(QWidget * parentWidget, modbus::Client * client, const QString & clientName):
	m_uiDelegate(parentWidget, client, clientName)
{
}

widgets::UIVisitorDelegate * VisitorDelegate::ui()
{
	return & m_uiDelegate;
}

}
}
