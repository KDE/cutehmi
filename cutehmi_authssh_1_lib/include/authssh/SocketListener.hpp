#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_SOCKETLISTENER_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_SOCKETLISTENER_HPP

#include <QObject>

namespace cutehmi {
namespace authssh {

class SocketListener:
	public QObject
{
	Q_OBJECT

	public:
		explicit SocketListener(QObject * parent = nullptr);

//		~SocketListener() override;

//		bool start();

//		bool stop();

	signals:

	public slots:
//		void addConnection();

	private:
//		QTcpServer *m_server;
//		QVector<Client *> m_connections;
//		ssh_session m_session;
};

}
}

#endif
