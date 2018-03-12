#ifndef H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_RTUCONNECTION_HPP
#define H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_RTUCONNECTION_HPP

#include "common.hpp"
#include "LibmodbusConnection.hpp"

#include <modbus/modbus.h>

#include <QString>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * RTU connection.
 */
class CUTEHMI_MODBUS_API RTUConnection:
	public LibmodbusConnection
{
	typedef LibmodbusConnection Parent;

	public:
		enum class Parity : int
		{
			NONE,
			EVEN,
			ODD
		};

		enum class DataBits : int
		{
			BITS_5 = 5,
			BITS_6 = 6,
			BITS_7 = 7,
			BITS_8 = 8,
		};

		enum class StopBits : int
		{
			BITS_1 = 1,
			BITS_2 = 2
		};

//<workaround id="cutehmi_modbus_1-1" target="libmodbus" cause="bug">
//		enum class Mode : int
//		{
//			RS232 = MODBUS_RTU_RS232,
//			RS485 = MODBUS_RTU_RS485
//		};
//</workaround>
//<workaround id="cutehmi_modbus_1-2" target="cutehmi_modbus_1" cause="cutehmi_modbus_1-1">
		enum class Mode : int
		{
			RS232 = MODBUS_RTU_RS232
		};
//</workaround>

		/**
		 * Constructor.
		 * @param port port.
		 * @param baudRate baud rate.
		 * @param parity parity.
		 * @param dataBits data bits.
		 * @param stopBits stop bits.
		 * @param mode serial mode.
		 * @param slaveId slave id or slave number. Sometimes also called station address.
		 *
		 * @throw Exception.
		 */
		RTUConnection(const QString & port, int baudRate = 19200, Parity parity = Parity::NONE, DataBits dataBits = DataBits::BITS_8, StopBits stopBits = StopBits::BITS_1, Mode mode = Mode::RS232, int slaveId = 0) noexcept(false);

		virtual ~RTUConnection();

		const QString & port() const;

		int baudRate() const;

		Parity parity() const;

		DataBits dataBits() const;

		StopBits stopBits() const;

		Mode mode() const;

		int slaveId() const;

	private:
		static char ToLibmodbusParity(Parity parity);

		struct Members
		{
			QString port;
			int baudRate;
			Parity parity;
			DataBits dataBits;
			StopBits stopBits;
			Mode mode;
			int slaveId;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
