#include <cutehmi/modbus/internal/RTUClientConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

RTUClientConfig::RTUClientConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString RTUClientConfig::port() const
{
	QReadLocker locker(& m->lock);

	return m->port;
}

void RTUClientConfig::setPort(const QString & port)
{
	QWriteLocker locker(& m->lock);

	m->port = port;

	emit configChanged();
}

QSerialPort::Parity RTUClientConfig::parity() const
{
	QReadLocker locker(& m->lock);

	return m->parity;
}

void RTUClientConfig::setParity(QSerialPort::Parity parity)
{
	QWriteLocker locker(& m->lock);

	m->parity = parity;

	emit configChanged();
}

QSerialPort::BaudRate RTUClientConfig::baudRate() const
{
	QReadLocker locker(& m->lock);

	return m->baudRate;
}

void RTUClientConfig::setBaudRate(QSerialPort::BaudRate baudRate)
{
	QWriteLocker locker(& m->lock);

	m->baudRate = baudRate;

	emit configChanged();
}

QSerialPort::DataBits RTUClientConfig::dataBits() const
{
	QReadLocker locker(& m->lock);

	return m->dataBits;
}

void RTUClientConfig::setDataBits(QSerialPort::DataBits dataBits)
{
	QWriteLocker locker(& m->lock);

	m->dataBits = dataBits;

	emit configChanged();
}

QSerialPort::StopBits RTUClientConfig::stopBits() const
{
	QReadLocker locker(& m->lock);

	return m->stopBits;
}

void RTUClientConfig::setStopBits(QSerialPort::StopBits stopBits)
{
	QWriteLocker locker(& m->lock);

	m->stopBits = stopBits;

	emit configChanged();
}

int RTUClientConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);

	return m->slaveAddress;
}

void RTUClientConfig::setSlaveAddress(int slaveId)
{
	QWriteLocker locker(& m->lock);

	m->slaveAddress = slaveId;

	emit configChanged();
}

}
}
}
