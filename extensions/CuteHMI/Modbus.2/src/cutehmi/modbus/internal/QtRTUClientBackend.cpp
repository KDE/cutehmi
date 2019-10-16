#include <cutehmi/modbus/internal/QtRTUClientBackend.hpp>

#include <QModbusRtuSerialMaster>

namespace cutehmi {
namespace modbus {
namespace internal {

QtRTUClientBackend::QtRTUClientBackend(RTUClientConfig * config, QObject * parent):
	QtClientBackend(std::make_unique<QModbusRtuSerialMaster>(), parent),
	m(new Members(config))
{
}

int QtRTUClientBackend::slaveAddress() const
{
	return m->config->slaveAddress();
}

void QtRTUClientBackend::configureConnection()
{
	qClient()->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m->config->port());
	qClient()->setConnectionParameter(QModbusDevice::SerialParityParameter, m->config->parity());
	qClient()->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m->config->baudRate());
	qClient()->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, m->config->dataBits());
	qClient()->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, m->config->stopBits());

	CUTEHMI_DEBUG("Client configured on '" << m->config->port()	<< "', " << m->config->baudRate()
			<< ", " << m->config->parity()
			<< ", " << m->config->dataBits()
			<< ", " << m->config->stopBits()
			<< ".");
}

}
}
}
