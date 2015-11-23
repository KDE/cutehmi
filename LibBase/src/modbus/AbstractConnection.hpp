#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_ABSTRACTCONNECTION_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_ABSTRACTCONNECTION_HPP

#include "Exception.hpp"
#include "../utils/NonCopyable.hpp"
#include "../utils/NonMovable.hpp"

#include <QObject>

namespace modbus {

/**
 * Abstract connection.
 */
class CUTEHMI_API AbstractConnection:
	public utils::NonCopyable,
	public utils::NonMovable
{
	public:
		virtual ~AbstractConnection() = default;

		virtual void connect() = 0;

		virtual void disconnect() = 0;

	protected:
		AbstractConnection() = default;
};

}

#endif
