#ifndef INCLUDECUTEHMIMODBUSINTERNALTCPCLIENTCONFIG_HPP
#define INCLUDECUTEHMIMODBUSINTERNALTCPCLIENTCONFIG_HPP

#include "Config.hpp"

#include <QObject>
#include <QString>
#include <QReadWriteLock>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE TCPClientConfig:
	public Config
{
		Q_OBJECT

	public:
		static constexpr int MIN_SLAVE_ADDRESS = 1; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static constexpr int MAX_SLAVE_ADDRESS = 247; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static constexpr const char * INITIAL_HOST = "localhost";
		static constexpr int INITIAL_PORT = 502;
		static constexpr int INITIAL_SLAVE_ADDRESS = MIN_SLAVE_ADDRESS;

		explicit TCPClientConfig(QObject * parent = nullptr);

		QString host() const;

		void setHost(const QString & host);

		int port() const;

		void setPort(int port);

		int slaveAddress() const;

		void setSlaveAddress(int slaveAddress);

	private:
		struct Members
		{
			QString host = INITIAL_HOST;
			int	port = INITIAL_PORT;
			int slaveAddress = INITIAL_SLAVE_ADDRESS;
			mutable QReadWriteLock lock;
		};

		MPtr<Members> m;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALTCPSERVERCONFIG_HPP
