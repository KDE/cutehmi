#include <cutehmi/modbus/internal/TCPClientConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

TCPClientConfig::TCPClientConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString cutehmi::modbus::internal::TCPClientConfig::host() const
{
	QReadLocker locker(& m->lock);

	return m->host;
}

void TCPClientConfig::setHost(const QString & host)
{
	QWriteLocker locker(& m->lock);

	m->host = host;

	emit configChanged();
}

int cutehmi::modbus::internal::TCPClientConfig::port() const
{
	QReadLocker locker(& m->lock);

	return m->port;
}

void cutehmi::modbus::internal::TCPClientConfig::setPort(int port)
{
	QWriteLocker locker(& m->lock);

	m->port = port;

	emit configChanged();
}

int TCPClientConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);

	return m->slaveAddress;
}

void TCPClientConfig::setSlaveAddress(int slaveAddress)
{
	QWriteLocker locker(& m->lock);

	m->slaveAddress = slaveAddress;

	emit configChanged();
}

}
}
}
