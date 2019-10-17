#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_TCPSERVER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_TCPSERVER_HPP

#include "AbstractServer.hpp"
#include "internal/RegisterTraits.hpp"
#include "internal/QtTCPServerBackend.hpp"

#include <cutehmi/macros.hpp>

#include <QThread>
#include <QStateMachine>
#include <QModbusTcpServer>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API TCPServer:
	public AbstractServer
{
		Q_OBJECT

	public:
		static constexpr int MIN_SLAVE_ADDRESS = internal::TCPServerConfig::MIN_SLAVE_ADDRESS;
		static constexpr int MAX_SLAVE_ADDRESS = internal::TCPServerConfig::MAX_SLAVE_ADDRESS;
		static const char * INITIAL_HOST;
		static constexpr int INITIAL_PORT = internal::TCPServerConfig::INITIAL_PORT;
		static constexpr int INITIAL_SLAVE_ADDRESS = internal::TCPServerConfig::INITIAL_SLAVE_ADDRESS;
		static constexpr int INITIAL_COILS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_COILS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_COILS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_COILS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX;

		Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
		Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
		Q_PROPERTY(int slaveAddress READ slaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)

		TCPServer(QObject * parent = nullptr);

		~TCPServer() override;

		QString host() const;

		void setHost(const QString & host);

		int port() const;

		void setPort(int port);

		int slaveAddress() const;

		void setSlaveAddress(int slaveAddress);

		void setBusy(bool busy) override;

	public slots:
		void open() override;

		void close() override;

	signals:
		void hostChanged();

		void portChanged();

		void slaveAddressChanged();

	private:
		struct Members
		{
			internal::TCPServerConfig config;
			internal::QtTCPServerBackend backend;
			QThread thread;

			Members(internal::QtTCPServer::CoilDataContainer * coilData,
					internal::QtTCPServer::DiscreteInputDataContainer * discreteInputData,
					internal::QtTCPServer::HoldingRegisterDataContainer * holdingRegisterData,
					internal::QtTCPServer::InputRegisterDataContainer * inputRegisterData):
				backend(& config, coilData, discreteInputData, holdingRegisterData, inputRegisterData)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif
