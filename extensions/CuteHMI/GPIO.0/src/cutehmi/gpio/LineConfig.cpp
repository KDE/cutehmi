#include <cutehmi/gpio/LineConfig.hpp>

namespace cutehmi {
namespace gpio {

LineConfig::LineConfig(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

LineConfig::Direction LineConfig::direction() const
{
	return m->direction;
}

void LineConfig::setDirection(LineConfig::Direction direction)
{
	if (m->direction != direction) {
		m->direction = direction;
		emit directionChanged();
	}
}

LineConfig::ActiveState LineConfig::activeState() const
{
	return m->activeState;
}

void LineConfig::setActiveState(LineConfig::ActiveState activeState)
{
	if (m->activeState != activeState) {
		m->activeState = activeState;
		emit activeStateChanged();
	}
}

bool LineConfig::openDrain() const
{
	return m->openDrain;
}

void LineConfig::setOpenDrain(bool openDrain)
{
	if (m->openDrain != openDrain) {
		m->openDrain = openDrain;
		emit openDrainChanged();
	}
}

bool LineConfig::openSource() const
{
	return m->openSource;
}

void LineConfig::setOpenSource(bool openSource)
{
	if (m->openSource != openSource) {
		m->openSource = openSource;
		emit openSourceChanged();
	}
}

}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
