#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_RTUCONNECTION_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_RTUCONNECTION_HPP

#include "AbstractConnection.hpp"

#include <modbus.h>

#include <QString>

namespace modbus {

class CUTEHMI_API RTUConnection:
		public AbstractConnection
{
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

		enum class Mode : int
		{
			RS232 = MODBUS_RTU_RS232,
			RS485 = MODBUS_RTU_RS485
		};

		RTUConnection(const QString & port, int baudRate = 19200, Parity parity = Parity::NONE, DataBits dataBits = DataBits::BITS_8, StopBits stopBits = StopBits::BITS_1, Mode mode = Mode::RS232);

		virtual ~RTUConnection();

		void connect() override;

		void disconnect() override;

	private:
		QString m_port;
		int m_baudRate;
		Parity m_parity;
		DataBits m_dataBits;
		StopBits m_stopBits;
		Mode m_mode;
		bool m_connected;
		modbus_t * m_context;
};

}

#endif
