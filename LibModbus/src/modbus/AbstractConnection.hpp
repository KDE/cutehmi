#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_ABSTRACTCONNECTION_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_ABSTRACTCONNECTION_HPP

#include "Exception.hpp"

#include <utils/NonCopyable.hpp>
#include <utils/NonMovable.hpp>

#include <modbus.h>

namespace modbus {

/**
 * Abstract connection.
 */
class CUTEHMI_MODBUS_API AbstractConnection:
	public utils::NonCopyable,
	public utils::NonMovable
{
	public:
		struct Timeout {
			uint32_t sec;
			uint32_t usec;
		};

		virtual ~AbstractConnection() = default;

		/**
		 * Set byte timeout.
		 * @param timeout timeout parameter. @a timeout.usec must be in the range [0, 999999].
		 */
		void setByteTimeout(Timeout timeout);

		/**
		 * Get byte timeout.
		 * @return byte timeout.
		 */
		Timeout byteTimeout() const;

		/**
		 * Set response timeout.
		 * @param timeout timeout parameter. @a timeout.usec must be in the range [0, 999999].
		 */
		void setResponseTimeout(Timeout timeout);

		/**
		 * Get response timeout.
		 * @return  response timeout.
		 */
		Timeout responseTimeout() const;

		bool connected() const;

		virtual void connect();

		virtual void disconnect();

		virtual int readIr(int addr, int num, uint16_t & dest);

		virtual int readR(int addr, int num, uint16_t & dest);

		virtual int writeR(int addr, uint16_t value);


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
