#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_LIBMODBUSCONNECTION_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_LIBMODBUSCONNECTION_HPP

#include "Exception.hpp"
#include "AbstractConnection.hpp"

#include <utils/NonCopyable.hpp>
#include <utils/NonMovable.hpp>

#include <modbus.h>

namespace cutehmi {
namespace modbus {

/**
 * Abstract connection.
 */
class CUTEHMI_MODBUS_API LibmodbusConnection:
	public AbstractConnection,
	public utils::NonCopyable,
	public utils::NonMovable
{
	public:
		struct Timeout {
			uint32_t sec;
			uint32_t usec;
		};

		virtual ~LibmodbusConnection() = default;

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

		bool connect() override;

		void disconnect() override;

		int readIr(int addr, int num, uint16_t * dst) override;

		int readR(int addr, int num, uint16_t * dst) override;

		int writeR(int addr, uint16_t value) override;

		int readIb(int addr, int num, uint8_t * dst) override;

		int readB(int addr, int num, uint8_t * dst) override;

		int writeB(int addr, bool value) override;

	protected:
		LibmodbusConnection(modbus_t * context);

		const modbus_t * context() const;

		modbus_t * context();

		void setContext(modbus_t * context);

	private:
		modbus_t * m_context;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
