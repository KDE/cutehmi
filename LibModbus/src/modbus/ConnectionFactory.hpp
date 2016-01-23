#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_CONNECTIONFACTORY_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_CONNECTIONFACTORY_HPP

#include "../platform.hpp"

namespace modbus {

class AbstractConnection;

class CUTEHMI_MODBUS_API ConnectionFactory
{
	public:
		enum class ConnectionType
		{
			RTU,
			TCP
		};

		/**
		 * Create connection object.
		 * @param type connection type.
		 * @return connection object.
		 *
		 * @note caller is responsible for deleting received object.
		 */
		static AbstractConnection * Create(ConnectionType type);
};

}

#endif
