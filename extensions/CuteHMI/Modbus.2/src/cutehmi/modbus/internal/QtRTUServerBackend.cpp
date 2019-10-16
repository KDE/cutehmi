#include <cutehmi/modbus/internal/QtRTUServerBackend.hpp>
#include <cutehmi/modbus/internal/functions.hpp>

#include <QThread>
#include <QJsonArray>

namespace cutehmi {
namespace modbus {
namespace internal {

QtRTUServerBackend::QtRTUServerBackend(RTUServerConfig * config,
		QtRTUServer::CoilDataContainer * coilData,
		QtRTUServer::DiscreteInputDataContainer * discreteInputData,
		QtRTUServer::HoldingRegisterDataContainer * holdingRegisterData,
		QtRTUServer::InputRegisterDataContainer * inputRegisterData,
		QObject * parent):
	QtServerBackend(std::make_unique<QtRTUServer>(coilData, discreteInputData, holdingRegisterData, inputRegisterData), parent),
	m(new Members{config})
{
}

int QtRTUServerBackend::slaveId() const
{
	return m->config->slaveAddress();
}

void QtRTUServerBackend::configureConnection()
{
	qServer()->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m->config->port());
	qServer()->setConnectionParameter(QModbusDevice::SerialParityParameter, m->config->parity());
	qServer()->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m->config->baudRate());
	qServer()->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, m->config->dataBits());
	qServer()->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, m->config->stopBits());

	CUTEHMI_DEBUG("Server configured on '" << m->config->port()	<< "', " << m->config->baudRate()
			<< ", " << m->config->parity()
			<< ", " << m->config->dataBits()
			<< ", " << m->config->stopBits()
			<< ".");
}

}
}
}
