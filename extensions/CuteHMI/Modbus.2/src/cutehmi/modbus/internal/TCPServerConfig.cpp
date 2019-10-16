#include <cutehmi/modbus/internal/TCPServerConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

TCPServerConfig::TCPServerConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString cutehmi::modbus::internal::TCPServerConfig::host() const
{
	QReadLocker locker(& m->lock);
	return m->host;
}

void TCPServerConfig::setHost(const QString & host)
{
	QWriteLocker locker(& m->lock);
	m->host = host;
	emit configChanged();
}

int cutehmi::modbus::internal::TCPServerConfig::port() const
{
	QReadLocker locker(& m->lock);
	return m->port;
}

void cutehmi::modbus::internal::TCPServerConfig::setPort(int port)
{
	QWriteLocker locker(& m->lock);
	m->port = port;
	emit configChanged();
}

int cutehmi::modbus::internal::TCPServerConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);
	return m->slaveAddress;
}

void TCPServerConfig::setSlaveAddress(int address)
{
	QWriteLocker locker(& m->lock);
	m->slaveAddress = address;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::coilsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->coilsAddressRange;
}

void TCPServerConfig::setCoilsAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->coilsAddressRange = addressRange;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::inputRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->inputRegistersAddressRange;
}

void TCPServerConfig::setInputRegistersAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->inputRegistersAddressRange = addressRange;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::discreteInputsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->discreteInputsAddressRange;
}

void TCPServerConfig::setDiscreteInputsAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->discreteInputsAddressRange = addressRange;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::holdingRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->holdingRegistersAddressRange;
}

void TCPServerConfig::setHoldingRegistersAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->holdingRegistersAddressRange = addressRange;
	emit configChanged();
}

}
}
}
