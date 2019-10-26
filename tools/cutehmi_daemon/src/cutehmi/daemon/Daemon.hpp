#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_HPP

#include "CoreData.hpp"

#include <functional>

namespace cutehmi {
namespace daemon {

class _Daemon;

class Daemon final
{
	public:
		static constexpr int EXIT_AGAIN = 129;	// 128 + SIGHUP (1).

		Daemon(CoreData * data, std::function<int(CoreData &)> & core);

		~Daemon();	// Non-virtual destructor, but class is final.

		int exitCode() const;

	protected:
		void setExitCode(int exitCode);

		int exec();

		CoreData * data() const;

	private:
		void _init();

		void _exec();

		void _destroy();

		CoreData * m_data;
		std::function<int(CoreData &)> & m_core;
		int m_exitCode;
		_Daemon * _daemon;
};

}
}

#endif

//(c)MP: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
