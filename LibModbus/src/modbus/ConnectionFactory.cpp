#include "ConnectionFactory.hpp"
#include "RTUConnection.hpp"
#include "TCPConnection.hpp"

#include <QObject>
#include <QtDebug>

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
			qFatal("Unrecognized connection type (%d).", type);
			return 0;
	}
}

}
