#include "ConnectionFactory.hpp"
#include "RTUConnection.hpp"
#include "TCPConnection.hpp"

#include <QObject>

namespace modbus {

AbstractConnection * ConnectionFactory::Create(ConnectionType type)
{
	switch (type) {
		case ConnectionType::RTU:
			///@todo Hard coding "COM1" temporary - default should be system independent.
			return new RTUConnection("COM1");
		case ConnectionType::TCP:
			return new TCPConnection("127.0.0.1");
		default:
			qFatal(QObject::tr("Can not create connection object of unrecognized type: %1").arg(static_cast<int>(type)).toLocal8Bit().constData());
			return 0;
	}
}

}
