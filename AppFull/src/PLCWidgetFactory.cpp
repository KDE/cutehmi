#include "PLCWidgetFactory.hpp"
#include "modbus/widgets/ClientControlWidget.hpp"

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
	return new modbus::widgets::ClientControlWidget(client, 0);
}
