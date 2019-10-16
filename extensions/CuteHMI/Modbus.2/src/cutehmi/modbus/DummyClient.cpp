#include <cutehmi/modbus/DummyClient.hpp>

#include <cutehmi/modbus/internal/HoldingRegisterPolling.hpp>

#include <QJsonArray>

namespace cutehmi {
namespace modbus {

constexpr int DummyClient::INITIAL_OPEN_LATENCY;
constexpr int DummyClient::INITIAL_CLOSE_LATENCY;
constexpr int DummyClient::INITIAL_LATENCY;

DummyClient::DummyClient(QObject * parent):
	AbstractClient(parent),
	m(new Members)
{
	m->backend.moveToThread(& m->thread);

	connect(& m->thread, & QThread::finished, & m->backend, & internal::DummyClientBackend::ensureClosed);

	connect(this, & DummyClient::requestReceived, & m->backend, & internal::DummyClientBackend::processRequest);

	connect(& m->backend, & internal::DummyClientBackend::replied, this, & DummyClient::handleReply);

	connect(& m->backend, & internal::DummyClientBackend::stateChanged, this, & DummyClient::setState);

	connect(& m->backend, & internal::DummyClientBackend::closed, this, & DummyClient::stopped);

	connect(& m->backend, & internal::DummyClientBackend::opened, this, & DummyClient::started);

	connect(& m->backend, & internal::DummyClientBackend::errored, this, & DummyClient::broke);
	connect(& m->backend, & internal::DummyClientBackend::closed, this, & DummyClient::broke);

	m->thread.start();
}

DummyClient::~DummyClient()
{
	m->thread.quit();
	m->thread.wait();
}

int DummyClient::connectLatency() const
{
	return m->config.openLatency();
}

void DummyClient::setConnectLatency(int connectLatency)
{
	if (m->config.openLatency() != connectLatency) {
		m->config.setOpenLatency(connectLatency);
		emit connectLatencyChanged();
	}
}

int DummyClient::disconnectLatency() const
{
	return m->config.closeLatency();
}

void DummyClient::setDisconnectLatency(int disconnectLatency)
{
	if (m->config.closeLatency() != disconnectLatency) {
		m->config.setCloseLatency(disconnectLatency);
		emit disconnectLatencyChanged();
	}
}

int DummyClient::latency() const
{
	return m->config.latency();
}

void DummyClient::setLatency(int latency)
{
	if (m->config.latency() != latency) {
		m->config.setLatency(latency);
		emit latencyChanged();
	}
}

void DummyClient::open()
{
	emit m->backend.openRequested();
}

void DummyClient::close()
{
	emit m->backend.closeRequested();
}

}
}
