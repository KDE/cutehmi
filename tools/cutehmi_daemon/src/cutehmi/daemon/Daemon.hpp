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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
