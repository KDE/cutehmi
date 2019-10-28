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

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
