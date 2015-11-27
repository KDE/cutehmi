#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_ABSTRACTCONNECTION_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_ABSTRACTCONNECTION_HPP

#include "Exception.hpp"
#include "../utils/NonCopyable.hpp"
#include "../utils/NonMovable.hpp"

#include <modbus.h>

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

		bool connected() const;

		virtual void connect();

		virtual void disconnect();

		virtual int readIr(int addr, int num, uint16_t & dest);

		virtual int readR(int addr, int num, uint16_t & dest);

	protected:
		AbstractConnection(modbus_t * context);

		const modbus_t * context() const;

		modbus_t * context();

		void setContext(modbus_t * context);

		void setConnected(bool connected);

	private:
		modbus_t * m_context;
		bool m_connected;
};

}

#endif
