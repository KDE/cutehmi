#include <cutehmi/modbus/internal/QtRTUServer.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

QtRTUServer::QtRTUServer(CoilDataContainer * coilData,
		DiscreteInputDataContainer * discreteInputData,
		HoldingRegisterDataContainer * holdingRegisterData,
		InputRegisterDataContainer * inputRegisterData,
		QObject * parent):
	QModbusRtuSerialSlave(parent),
	m(new Members{coilData, discreteInputData, holdingRegisterData, inputRegisterData})
{
}

bool QtRTUServer::setMap(const QModbusDataUnitMap & map)
{
	return Mixin::setMap(map);
}

bool QtRTUServer::readData(QModbusDataUnit * newData) const
{
	return Mixin::readData(newData);
}

bool QtRTUServer::writeData(const QModbusDataUnit & newData)
{
	return Mixin::writeData(newData);
}

}
}
}
