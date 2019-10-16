#include <cutehmi/modbus/internal/QtTCPClientBackend.hpp>

#include <QModbusTcpClient>

namespace cutehmi {
namespace modbus {
namespace internal {

QtTCPClientBackend::QtTCPClientBackend(TCPClientConfig * config, QObject * parent):
	QtClientBackend(std::make_unique<QModbusTcpClient>(), parent),
	m(new Members(config))
{
}

int QtTCPClientBackend::slaveAddress() const
{
	return m->config->slaveAddress();
}

void QtTCPClientBackend::configureConnection()
{
	qClient()->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m->config->host());
	qClient()->setConnectionParameter(QModbusDevice::NetworkPortParameter, m->config->port());

	CUTEHMI_DEBUG("Client configured on '" << m->config->host() << ":" << m->config->port() << "'.");
}

}
}
}
