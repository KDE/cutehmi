#include "../../../include/cutehmi/services/Service.hpp"

namespace cutehmi {
namespace services {

constexpr const char * Service::INITIAL_NAME;
constexpr Service::State Service::INITIAL_STATE;

Service::Service(const QString & name, QObject * parent):
	QObject(parent),
	m(new Members{name, STOPPED})
{
}

const QString & Service::name() const
{
	return m->name;
}

void Service::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

Service::State Service::state() const
{
	return m->state;
}

void Service::start()
{
	if (state() != STOPPED) {
		CUTEHMI_LOG_WARNING("Service::start() failed to start the service, because it is not in STOPPED state.");
		return;
	}
	setState(customStart());
}

void Service::stop()
{
	if (state() == STOPPED)
		return;
	setState(customStop());
}

void Service::setState(State state)
{
	if (m->state != state) {
		std::swap(m->state, state);
		emit stateChanged(state, m->state);
	}
}

Service::State Service::customStart()
{
	return STARTED;
}

Service::State Service::customStop()
{
	return STOPPED;
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
