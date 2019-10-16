#ifndef INCLUDECUTEHMIMODBUSINTERNALRTUCLIENTCONFIG_HPP
#define INCLUDECUTEHMIMODBUSINTERNALRTUCLIENTCONFIG_HPP

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
		static constexpr const char * INITIAL_PORT = "COM1";
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

#endif // INCLUDECUTEHMIMODBUSINTERNALTCPSERVERCONFIG_HPP
