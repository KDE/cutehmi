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

//(c)C: Copyright © 2018-2019, Michal Policht <michal@policht.pl>, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
