#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_HPP

//#include "platform.hpp"
//#include "LogfileBuf.hpp"

#include <QString>
#include <QFile>

namespace cutehmi {
namespace daemon {

//class Core;

class Daemon final
{
	public:
//		static constexpr int SLEEP_UNIT = 1000;

		Daemon();

		~Daemon();	// Non-virtual destructor, but class is final.

//		void exec(int maxFails = 3);

	protected:
		void terminate();

	private:
		void _init();

		void _destroy();

		void _watch();

		bool m_terminate;
};

}
}

#endif
