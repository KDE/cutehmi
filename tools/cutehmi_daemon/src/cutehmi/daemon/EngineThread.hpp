#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_ENGINETHREAD_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_ENGINETHREAD_HPP

#include <QThread>

namespace cutehmi {
namespace daemon {

class EngineThread:
	public QThread
{
	Q_OBJECT

	public:
		EngineThread(QObject * parent = nullptr);

	signals:
		void loadRequested(const QString & project);
};

}
}

#endif
