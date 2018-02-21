#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_INTERNAL_TUNNELENTRANCE_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_INTERNAL_TUNNELENTRANCE_HPP

#include "common.hpp"

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QDataStream>

class QTcpSocket;
class QTcpServer;

namespace cutehmi {
namespace authssh {
namespace internal {

class TunnelEntrance:
	public QObject
{
	Q_OBJECT

	public:
		explicit TunnelEntrance(const QHostAddress & host, uint port, QObject * parent = nullptr);

		~TunnelEntrance() override;

		qint64 bytesAvailable() const;

		int read(QByteArray & data);

		qint64 write(const QByteArray & data);

		bool open();

		void close();

	public slots:
//		void write(QDataStream & data);

	signals:
		void readyRead();

	private slots:
		void establishConnection();

		void removeConnection();

		void readData();

	private:
		struct Members
		{
			QHostAddress host;
			uint port;
			QTcpServer * tcpServer;
			QTcpSocket * connection;
			QByteArray data;

			Members(const QHostAddress & p_host, uint p_port):
				host(p_host),
				port(p_port),
				tcpServer(new QTcpServer),
				connection(nullptr)
			{
			}

			~Members()
			{
				tcpServer->deleteLater();
				tcpServer = nullptr;
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif
