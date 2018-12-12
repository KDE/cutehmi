#ifndef STUPID_SRC_DAEMON_HPP
#define STUPID_SRC_DAEMON_HPP

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
		static void MessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg);

		void terminate();

	private:
		void _init();

		void _watch();

		bool m_terminate;
};

}
}

#endif
