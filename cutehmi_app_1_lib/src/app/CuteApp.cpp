#include "../../include/app/CuteApp.hpp"

namespace cutehmi {
namespace app {

CuteApp::CuteApp(int & argc, char ** argv):
	Parent(argc, argv),
	m(new Members)
{
	m->updateTimer.setTimerType(Qt::VeryCoarseTimer);
	connect(& m->updateTimer, & QTimer::timeout, this, & CuteApp::updateIdleTime);
}

double CuteApp::idle() const
{
	return m->idle;
}

bool CuteApp::idleMeasureEnabled() const
{
	return m->idleMeasureEnabled;
}

void CuteApp::setIdleMeasureEnabled(bool idleEnabled)
{
	if (m->idleMeasureEnabled != idleEnabled) {
		m->idleMeasureEnabled = idleEnabled;
		if (idleEnabled) {
			m->notifyEventCtr = 0;
			setIdle(0.0);
			m->idleTime.start();
			m->updateTimer.start(IDLE_MEASURE_INTERVAL);
		} else {
			setIdle(0.0);
			m->updateTimer.stop();
		}
		emit idleMeasureEnabledChanged();
	}
}

bool CuteApp::notify(QObject * receiver, QEvent * event)
{
	if (event->spontaneous())
		m->notifyEventCtr++;
	return Parent::notify(receiver, event);
}

void CuteApp::updateIdleTime()
{
	if (m->notifyEventCtr) {
		setIdle(0.0);
		m->notifyEventCtr = 0;
	} else
		setIdle(idle() + static_cast<double>(m->idleTime.restart()) / 1000.0);
}

void CuteApp::setIdle(double idle)
{
	if (m->idle != idle) {
		m->idle = idle;
		emit idleChanged();
	}
}

CuteApp::Members::Members():
	notifyEventCtr(0),
	idle(0.0),
	idleMeasureEnabled(false)
{
}

}
}
