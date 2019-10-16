#include <cutehmi/modbus/internal/DummyClientConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

constexpr int DummyClientConfig::INITIAL_OPEN_LATENCY;
constexpr int DummyClientConfig::INITIAL_CLOSE_LATENCY;
constexpr int DummyClientConfig::INITIAL_LATENCY;

DummyClientConfig::DummyClientConfig(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

int DummyClientConfig::openLatency() const
{
	QReadLocker locker(& m->lock);
	return m->openLatency;
}

void DummyClientConfig::setOpenLatency(int openLatency)
{
	QWriteLocker locker(& m->lock);
	m->openLatency = openLatency;
	emit configChanged();
}

int DummyClientConfig::closeLatency() const
{
	QReadLocker locker(& m->lock);
	return m->closeLatency;
}

void DummyClientConfig::setCloseLatency(int closeLatency)
{
	QWriteLocker locker(& m->lock);
	m->closeLatency = closeLatency;
	emit configChanged();
}

int DummyClientConfig::latency() const
{
	QReadLocker locker(& m->lock);
	return m->latency;
}

void DummyClientConfig::setLatency(int latency)
{
	QWriteLocker locker(& m->lock);
	m->latency = latency;
	emit configChanged();
}

}
}
}
