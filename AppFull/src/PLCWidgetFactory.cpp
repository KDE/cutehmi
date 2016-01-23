#include "PLCWidgetFactory.hpp"
#include "modbus/ui/ClientControlWidget.hpp"

#include <base/PLCClientManager.hpp>

PLCWidgetFactory::PLCWidgetFactory()
//	m_parentWidget(new QWidget)
{
}

PLCWidgetFactory::~PLCWidgetFactory()
{
//	delete m_parentWidget;
}

QWidget * PLCWidgetFactory::createClientControlWidget(modbus::Client * client) const
{
	return new modbus::ui::ClientControlWidget(client, 0);
}
