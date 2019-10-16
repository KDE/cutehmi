#include <cutehmi/modbus/TCPServer.hpp>

namespace cutehmi {
namespace modbus {

constexpr int TCPServer::MIN_SLAVE_ADDRESS;
constexpr int TCPServer::MAX_SLAVE_ADDRESS;
const char * TCPServer::INITIAL_HOST = internal::TCPServerConfig::INITIAL_HOST;
constexpr int TCPServer::INITIAL_PORT;
constexpr int TCPServer::INITIAL_SLAVE_ADDRESS;
constexpr int TCPServer::INITIAL_COILS_ADDRESS_RANGE_MIN;
constexpr int TCPServer::INITIAL_COILS_ADDRESS_RANGE_MAX;
constexpr int TCPServer::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN;
constexpr int TCPServer::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX;
constexpr int TCPServer::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN;
constexpr int TCPServer::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX;
constexpr int TCPServer::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN;
constexpr int TCPServer::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX;

TCPServer::TCPServer(QObject * parent):
	AbstractServer(parent),
	m(new Members(& coilData(), & discreteInputData(), & holdingRegisterData(), & inputRegisterData()))
{
	m->backend.moveToThread(& m->thread);

	connect(& m->thread, & QThread::finished, & m->backend, & internal::QtTCPServerBackend::ensureClosed);

	connect(this, & TCPServer::requestReceived, & m->backend, & internal::QtTCPServerBackend::processRequest);

	connect(& m->backend, & internal::AbstractServerBackend::busyUpdated, this, & TCPServer::updateBusy);

	connect(& m->backend, & internal::AbstractServerBackend::replied, this, & TCPServer::handleReply);

	connect(& m->backend, & internal::AbstractServerBackend::stateChanged, this, & TCPServer::setState);

	connect(& m->backend, & internal::QtTCPServerBackend::closed, this, & TCPServer::stopped);

	connect(& m->backend, & internal::QtTCPServerBackend::errored, this, & TCPServer::broke);
	connect(& m->backend, & internal::QtTCPServerBackend::closed, this, & TCPServer::broke);

	connect(& m->backend, & internal::QtTCPServerBackend::opened, this, & TCPServer::started);

	connect(& m->backend, & internal::QtTCPServerBackend::coilsWritten, this, & TCPServer::handleCoilsWritten);
	connect(& m->backend, & internal::QtTCPServerBackend::discreteInputsWritten, this, & TCPServer::handleDiscreteInputsWritten);
	connect(& m->backend, & internal::QtTCPServerBackend::holdingRegistersWritten, this, & TCPServer::handleHoldingRegistersWritten);
	connect(& m->backend, & internal::QtTCPServerBackend::inputRegistersWritten, this, & TCPServer::handleInputRegistersWritten);

	m->thread.start();
}

TCPServer::~TCPServer()
{
	m->thread.quit();
	m->thread.wait();
}

QString TCPServer::host() const
{
	return m->config.host();
}

void TCPServer::setHost(const QString & host)
{
	if (m->config.host() != host) {
		m->config.setHost(host);
		emit hostChanged();
	}
}

int TCPServer::port() const
{
	return m->config.port();
}

void TCPServer::setPort(int port)
{
	if (m->config.port() != port) {
		m->config.setPort(port);
		emit portChanged();
	}
}

int TCPServer::slaveAddress() const
{
	return m->config.slaveAddress();
}

void TCPServer::setBusy(bool busy)
{
	emit m->backend.setBusyRequested(busy);
}

void TCPServer::setSlaveAddress(int slaveAddress)
{
	if (m->config.slaveAddress() != slaveAddress) {
		m->config.setSlaveAddress(slaveAddress);
		emit slaveAddressChanged();
	}
}

void TCPServer::open()
{
	emit m->backend.openRequested();
}

void TCPServer::close()
{
	emit m->backend.closeRequested();
}

}
}
