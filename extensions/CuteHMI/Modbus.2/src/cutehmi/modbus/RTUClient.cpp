#include <cutehmi/modbus/RTUClient.hpp>

namespace cutehmi {
namespace modbus {

constexpr int RTUClient::MIN_SLAVE_ADDRESS;
constexpr int RTUClient::MAX_SLAVE_ADDRESS;
const char * RTUClient::INITIAL_PORT = internal::RTUClientConfig::INITIAL_PORT;
constexpr QSerialPort::Parity RTUClient::INITIAL_PARITY;
constexpr QSerialPort::BaudRate RTUClient::INITIAL_BAUD_RATE;
constexpr QSerialPort::DataBits RTUClient::INITIAL_DATA_BITS;
constexpr QSerialPort::StopBits RTUClient::INITIAL_STOP_BITS;
constexpr int RTUClient::INITIAL_SLAVE_ADDRESS;

RTUClient::RTUClient(QObject * parent):
	AbstractClient(parent),
	m(new Members)
{
	m->backend.moveToThread(& m->thread);

	connect(& m->thread, & QThread::finished, & m->backend, & internal::QtClientBackend::ensureClosed);

	connect(this, & RTUClient::requestReceived, & m->backend, & internal::QtClientBackend::processRequest);

	connect(& m->backend, & internal::QtClientBackend::replied, this, & RTUClient::handleReply);

	connect(& m->backend, & internal::QtClientBackend::stateChanged, this, & RTUClient::setState);

	connect(& m->backend, & internal::QtClientBackend::closed, this, & RTUClient::stopped);

	connect(& m->backend, & internal::QtClientBackend::opened, this, & RTUClient::started);

	connect(& m->backend, & internal::QtClientBackend::errored, this, & RTUClient::broke);
	connect(& m->backend, & internal::QtClientBackend::closed, this, & RTUClient::broke);

	m->thread.start();
}

RTUClient::~RTUClient()
{
	m->thread.quit();
	m->thread.wait();
}

QString RTUClient::port() const
{
	return m->config.port();
}

void RTUClient::setPort(const QString & port)
{
	if (m->config.port() != port) {
		m->config.setPort(port);
		emit portChanged();
	}
}

QSerialPort::Parity RTUClient::parity() const
{
	return m->config.parity();
}

void RTUClient::setParity(QSerialPort::Parity parity)
{
	if (m->config.parity() != parity) {
		m->config.setParity(parity);
		emit parityChanged();
	}
}

QSerialPort::BaudRate RTUClient::baudRate() const
{
	return m->config.baudRate();
}

void RTUClient::setBaudRate(QSerialPort::BaudRate baudRate)
{
	if (m->config.baudRate() != baudRate) {
		m->config.setBaudRate(baudRate);
		emit baudRateChanged();
	}
}

QSerialPort::DataBits RTUClient::dataBits() const
{
	return m->config.dataBits();
}

void RTUClient::setDataBits(QSerialPort::DataBits dataBits)
{
	if (m->config.dataBits() != dataBits) {
		m->config.setDataBits(dataBits);
		emit dataBitsChanged();
	}
}

QSerialPort::StopBits RTUClient::stopBits() const
{
	return m->config.stopBits();
}

void RTUClient::setStopBits(QSerialPort::StopBits stopBits)
{
	if (m->config.stopBits() != stopBits) {
		m->config.setStopBits(stopBits);
		emit stopBitsChanged();
	}
}

int RTUClient::slaveAddress() const
{
	return m->config.slaveAddress();
}

void RTUClient::setSlaveAddress(int slaveAddress)
{
	if (m->config.slaveAddress() != slaveAddress) {
		m->config.setSlaveAddress(slaveAddress);
		emit slaveAddressChanged();
	}
}

void RTUClient::open()
{
	emit m->backend.openRequested();
}

void RTUClient::close()
{
	emit m->backend.closeRequested();
}

}
}
