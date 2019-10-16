#include <cutehmi/modbus/internal/QtTCPServerBackend.hpp>
#include <cutehmi/modbus/internal/functions.hpp>

#include <QThread>
#include <QJsonArray>

namespace cutehmi {
namespace modbus {
namespace internal {

QtTCPServerBackend::QtTCPServerBackend(TCPServerConfig * config,
		QtTCPServer::CoilDataContainer * coilData,
		QtTCPServer::DiscreteInputDataContainer * discreteInputData,
		QtTCPServer::HoldingRegisterDataContainer * holdingRegisterData,
		QtTCPServer::InputRegisterDataContainer * inputRegisterData,
		QObject * parent):
	QtServerBackend(std::make_unique<QtTCPServer>(coilData, discreteInputData, holdingRegisterData, inputRegisterData), parent),
	m(new Members{config})
{
}

int QtTCPServerBackend::slaveId() const
{
	return m->config->slaveAddress();
}

void QtTCPServerBackend::configureConnection()
{
	qServer()->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m->config->host());
	qServer()->setConnectionParameter(QModbusDevice::NetworkPortParameter, m->config->port());

	CUTEHMI_DEBUG("Server configured on '" << m->config->host() << ":" << m->config->port() << "'.");
}

}
}
}
