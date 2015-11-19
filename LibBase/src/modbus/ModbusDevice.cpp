#include "ModbusDevice.hpp"

namespace modbus {

InputRegister * ModbusDevice::irAt(QQmlListProperty<InputRegister> * , int )
{
//	IrDataContainer * irData = static_cast<IrDataContainer *>(ir->data);
//	IrDataContainer::const_iterator irIt = irData->find(index);
//	if (irIt == irData.end())

//	return & static_cast<ModbusInputRegister *>(property->data)[index];
	return 0;
}

int ModbusDevice::irCount(QQmlListProperty<InputRegister> * ir)
{
	Q_UNUSED(ir);

	return 100;
}

ModbusDevice::ModbusDevice(QObject * parent):
	QObject(parent),
	m_ir(this, & m_irData, ModbusDevice::irCount, ModbusDevice::irAt)
{
}

const QQmlListProperty<InputRegister> & ModbusDevice::ir() const
{
	return m_ir;
}

}
