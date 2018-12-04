#ifndef H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_LIBMODBUSCONNECTION_HPP
#define H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_LIBMODBUSCONNECTION_HPP

#include "common.hpp"
#include "AbstractConnection.hpp"
#include "../Exception.hpp"

#include <cutehmi/NonCopyable.hpp>
#include <cutehmi/NonMovable.hpp>

#include <modbus/modbus.h>

#include <QMutex>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Libmodbus connection.
 */
class CUTEHMI_MODBUS_API LibmodbusConnection:
	public AbstractConnection,
	public NonCopyable,
	public NonMovable
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

		bool connected() const override;

		int readIr(int addr, int num, uint16_t * dest) override;

		int readR(int addr, int num, uint16_t * dest) override;

		int writeR(int addr, uint16_t value) override;

		int readIb(int addr, int num, bool * dest) override;

		int readB(int addr, int num, bool * dest) override;

		int writeB(int addr, bool value) override;

	protected:
		LibmodbusConnection(modbus_t * context);

		const modbus_t * context() const;

		modbus_t * context();

		void setContext(modbus_t * context);

	private:
		static QMutex & Mutex(); // libmodbus functions are neither thread-safe nor re-entrant. A shared mutex is required to protect the data from corruption.

		struct Members
		{
			modbus_t * context;
			bool connected;
			std::vector<uint8_t> bIbBuffer;

			Members(modbus_t * p_context):
				context(p_context),
				connected(false)
			{
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
