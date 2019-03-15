#include "Daemon.hpp"

namespace cutehmi {
namespace daemon {

Daemon::Daemon(CoreData * data, std::function<int(CoreData &)> & core):
	m_data(data),
	m_core(core),
	m_exitCode(EXIT_FAILURE)
{
	//<cutehmi_daemon-silent_initialization.principle>
	_init();
	//</cutehmi_daemon-silent_initialization.principle>
}

Daemon::~Daemon()
{
	_destroy();
}

int Daemon::exitCode() const
{
	return m_exitCode;
}

void Daemon::setExitCode(int exitCode)
{
	m_exitCode = exitCode;
}

int Daemon::exec()
{
	do {
		_exec();
		m_exitCode = m_core(*m_data);
	} while (m_exitCode == EXIT_AGAIN);
	return m_exitCode;
}

CoreData * Daemon::data() const
{
	return m_data;
}

}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
