#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_RTUSERVER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_RTUSERVER_HPP

#include "AbstractServer.hpp"
#include "internal/RegisterTraits.hpp"
#include "internal/QtRTUServerBackend.hpp"

#include <cutehmi/macros.hpp>

#include <QThread>
#include <QStateMachine>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API RTUServer:
	public AbstractServer
{
		Q_OBJECT

	public:
		static constexpr int MIN_SLAVE_ADDRESS = internal::RTUServerConfig::MIN_SLAVE_ADDRESS;
		static constexpr int MAX_SLAVE_ADDRESS = internal::RTUServerConfig::MAX_SLAVE_ADDRESS;
		static const char * INITIAL_PORT;
		static constexpr QSerialPort::Parity INITIAL_PARITY = internal::RTUServerConfig::INITIAL_PARITY;
		static constexpr QSerialPort::BaudRate INITIAL_BAUD_RATE = internal::RTUServerConfig::INITIAL_BAUD_RATE;
		static constexpr QSerialPort::DataBits INITIAL_DATA_BITS = internal::RTUServerConfig::INITIAL_DATA_BITS;
		static constexpr QSerialPort::StopBits INITIAL_STOP_BITS = internal::RTUServerConfig::INITIAL_STOP_BITS;
		static constexpr int INITIAL_SLAVE_ADDRESS = internal::RTUServerConfig::INITIAL_SLAVE_ADDRESS;
		static constexpr int INITIAL_COILS_ADDRESS_RANGE_MIN = internal::RTUServerConfig::INITIAL_COILS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_COILS_ADDRESS_RANGE_MAX = internal::RTUServerConfig::INITIAL_COILS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN = internal::RTUServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX = internal::RTUServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN = internal::RTUServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX = internal::RTUServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN = internal::RTUServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX = internal::RTUServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX;

		Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged)
		Q_PROPERTY(QSerialPort::Parity parity READ parity WRITE setParity NOTIFY parityChanged)
		Q_PROPERTY(QSerialPort::BaudRate baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
		Q_PROPERTY(QSerialPort::DataBits dataBits READ dataBits WRITE setDataBits NOTIFY dataBitsChanged)
		Q_PROPERTY(QSerialPort::StopBits stopBits READ stopBits WRITE setStopBits NOTIFY stopBitsChanged)
		Q_PROPERTY(int slaveAddress READ slaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)
		Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

		RTUServer(QObject * parent = nullptr);

		~RTUServer() override;

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

		void setBusy(bool busy) override;

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
		struct Members
		{
			internal::RTUServerConfig config;
			internal::QtRTUServerBackend backend;
			QThread thread;

			Members(internal::QtRTUServer::CoilDataContainer * coilData,
					internal::QtRTUServer::DiscreteInputDataContainer * discreteInputData,
					internal::QtRTUServer::HoldingRegisterDataContainer * holdingRegisterData,
					internal::QtRTUServer::InputRegisterDataContainer * inputRegisterData):
				backend(& config, coilData, discreteInputData, holdingRegisterData, inputRegisterData)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif
