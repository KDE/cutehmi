#include <cutehmi/services/PollingTimer.hpp>

#include <QTimer>

namespace cutehmi {
namespace services {

constexpr int PollingTimer::INITIAL_INTERVAL;
constexpr int PollingTimer::INITIAL_SUBTIMER_INTERVAL;

PollingTimer::PollingTimer(int interval, QObject * parent):
	QObject(parent),
	m(new Members{interval, nullptr})
{
}

int PollingTimer::interval() const
{
	return m->interval;
}

void PollingTimer::setlInterval(int pollInterval)
{
	if (m->interval != pollInterval) {
		m->interval = pollInterval;
		emit intervalChanged();
	}
}

PollingTimer * PollingTimer::subtimer()
{
	if (m->subtimer == nullptr)
		m->subtimer = new PollingTimer(INITIAL_SUBTIMER_INTERVAL, this);
	return m->subtimer;
}

void PollingTimer::start()
{
	shoot();
}

void PollingTimer::shoot()
{
	QTimer::singleShot(interval(), this, & PollingTimer::triggered);
}

}
}
