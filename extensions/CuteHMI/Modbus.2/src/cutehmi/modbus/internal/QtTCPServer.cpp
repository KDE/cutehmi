#include <cutehmi/modbus/internal/QtTCPServer.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

QtTCPServer::QtTCPServer(CoilDataContainer * coilData,
		DiscreteInputDataContainer * discreteInputData,
		HoldingRegisterDataContainer * holdingRegisterData,
		InputRegisterDataContainer * inputRegisterData,
		QObject * parent):
	QModbusTcpServer(parent),
	m(new Members{coilData, discreteInputData, holdingRegisterData, inputRegisterData})
{
}

bool QtTCPServer::setMap(const QModbusDataUnitMap & map)
{
	return Mixin::setMap(map);
}

bool QtTCPServer::readData(QModbusDataUnit * newData) const
{
	return Mixin::readData(newData);
}

bool QtTCPServer::writeData(const QModbusDataUnit & newData)
{
	return Mixin::writeData(newData);
}

}
}
}
