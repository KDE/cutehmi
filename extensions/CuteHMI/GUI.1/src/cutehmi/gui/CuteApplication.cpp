#include "../../../include/cutehmi/gui/CuteApplication.hpp"

namespace cutehmi {
namespace gui {

CuteApplication::CuteApplication(int & argc, char ** argv):
	Parent(argc, argv),
	m(new Members)
{
	m->updateTimer.setTimerType(Qt::VeryCoarseTimer);
	connect(& m->updateTimer, & QTimer::timeout, this, & CuteApplication::updateIdleTime);
}

double CuteApplication::idle() const
{
	return m->idle;
}

bool CuteApplication::idleMeasureEnabled() const
{
	return m->idleMeasureEnabled;
}

void CuteApplication::setIdleMeasureEnabled(bool idleEnabled)
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

bool CuteApplication::notify(QObject * receiver, QEvent * event)
{
	if (event->spontaneous())
		m->notifyEventCtr++;
	return Parent::notify(receiver, event);
}

void CuteApplication::updateIdleTime()
{
	if (m->notifyEventCtr) {
		setIdle(0.0);
		m->notifyEventCtr = 0;
	} else
		setIdle(idle() + static_cast<double>(m->idleTime.elapsed()) / 1000.0);
	m->idleTime.restart();
}

void CuteApplication::setIdle(double idle)
{
	if (m->idle != idle) {
		m->idle = idle;
		emit idleChanged();
	}
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
