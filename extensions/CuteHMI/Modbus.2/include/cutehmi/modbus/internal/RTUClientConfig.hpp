#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_RTUCLIENTCONFIG_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_RTUCLIENTCONFIG_HPP

#include "Config.hpp"

#include <QObject>
#include <QString>
#include <QModbusDevice>
#include <QReadWriteLock>
#include <QSerialPort>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE RTUClientConfig:
	public Config
{
		Q_OBJECT

	public:
		static constexpr int MIN_SLAVE_ADDRESS = 1; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static constexpr int MAX_SLAVE_ADDRESS = 247; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static const char * INITIAL_PORT;
		static constexpr QSerialPort::Parity INITIAL_PARITY = QSerialPort::NoParity;
		static constexpr QSerialPort::BaudRate INITIAL_BAUD_RATE = QSerialPort::Baud19200;
		static constexpr QSerialPort::DataBits INITIAL_DATA_BITS = QSerialPort::Data8;
		static constexpr QSerialPort::StopBits INITIAL_STOP_BITS = QSerialPort::OneStop;
		static constexpr int INITIAL_SLAVE_ADDRESS = MIN_SLAVE_ADDRESS;

		explicit RTUClientConfig(QObject * parent = nullptr);

		QString port() const;

		void setPort(const QString & port);

		QSerialPort::Parity parity() const;

		void setParity(QSerialPort::Parity parity);

		QSerialPort::BaudRate baudRate() const;

		void setBaudRate(QSerialPort::BaudRate baudRate);

		QSerialPort::DataBits dataBits() const;

		void setDataBits(QSerialPort::DataBits dataBits);

		QSerialPort::StopBits stopBits() const;

		void setStopBits(QSerialPort::StopBits stopBits);

		int slaveAddress() const;

		void setSlaveAddress(int slaveAddress);

	private:
		struct Members
		{
			QString port = INITIAL_PORT;
			QSerialPort::Parity parity = INITIAL_PARITY;
			QSerialPort::BaudRate baudRate = INITIAL_BAUD_RATE;
			QSerialPort::DataBits dataBits = INITIAL_DATA_BITS;
			QSerialPort::StopBits stopBits = INITIAL_STOP_BITS;
			int slaveAddress = INITIAL_SLAVE_ADDRESS;
			mutable QReadWriteLock lock;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
