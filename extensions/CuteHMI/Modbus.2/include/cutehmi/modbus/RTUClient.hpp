#ifndef INCLUDECUTEHMIMODBUSRTUCLIENT_HPP
#define INCLUDECUTEHMIMODBUSRTUCLIENT_HPP

#include "AbstractClient.hpp"
#include "internal/QtRTUClientBackend.hpp"

#include <QThread>

namespace cutehmi {
namespace modbus {

/**
 * Modbus TCP client.
 */
class CUTEHMI_MODBUS_API RTUClient:
	public AbstractClient
{
		Q_OBJECT

	public:
		static constexpr int MIN_SLAVE_ADDRESS = internal::RTUClientConfig::MIN_SLAVE_ADDRESS;
		static constexpr int MAX_SLAVE_ADDRESS = internal::RTUClientConfig::MAX_SLAVE_ADDRESS;
		static const char * INITIAL_PORT;
		static constexpr QSerialPort::Parity INITIAL_PARITY = internal::RTUClientConfig::INITIAL_PARITY;
		static constexpr QSerialPort::BaudRate INITIAL_BAUD_RATE = internal::RTUClientConfig::INITIAL_BAUD_RATE;
		static constexpr QSerialPort::DataBits INITIAL_DATA_BITS = internal::RTUClientConfig::INITIAL_DATA_BITS;
		static constexpr QSerialPort::StopBits INITIAL_STOP_BITS = internal::RTUClientConfig::INITIAL_STOP_BITS;
		static constexpr int INITIAL_SLAVE_ADDRESS = internal::RTUClientConfig::INITIAL_SLAVE_ADDRESS;

		Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged)
		Q_PROPERTY(QSerialPort::Parity parity READ parity WRITE setParity NOTIFY parityChanged)
		Q_PROPERTY(QSerialPort::BaudRate baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
		Q_PROPERTY(QSerialPort::DataBits dataBits READ dataBits WRITE setDataBits NOTIFY dataBitsChanged)
		Q_PROPERTY(QSerialPort::StopBits stopBits READ stopBits WRITE setStopBits NOTIFY stopBitsChanged)
		Q_PROPERTY(int slaveAddress READ slaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)

		RTUClient(QObject * parent = nullptr);

		~RTUClient() override;

		QString port() const;

		void setPort(const QString & port);

		QSerialPort::Parity parity() const;

		void setParity(QSerialPort::Parity);

		QSerialPort::BaudRate baudRate() const;

		void setBaudRate(QSerialPort::BaudRate baudRate);

		QSerialPort::DataBits dataBits() const;

		void setDataBits(QSerialPort::DataBits dataBits);

		QSerialPort::StopBits stopBits() const;

		void setStopBits(QSerialPort::StopBits stopBits);

		int slaveAddress() const;

		void setSlaveAddress(int slaveAddress);

	public slots:
		void open() override;

		void close() override;

	signals:
		void portChanged();

		void parityChanged();

		void baudRateChanged();

		void dataBitsChanged();

		void stopBitsChanged();

		void slaveAddressChanged();

	private:
		struct Members {
			internal::RTUClientConfig config;
			internal::QtRTUClientBackend backend;
			QThread thread;

			Members():
				backend(& config)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // INCLUDECUTEHMIMODBUSTCPCLIENT_HPP
