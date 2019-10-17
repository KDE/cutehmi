#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTTCPSERVERBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTTCPSERVERBACKEND_HPP

#include "QtServerBackend.hpp"
#include "TCPServerConfig.hpp"
#include "QtTCPServer.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * TCP server backend.
 */
class CUTEHMI_MODBUS_PRIVATE QtTCPServerBackend:
	public QtServerBackend
{
		Q_OBJECT

	public:
		QtTCPServerBackend(TCPServerConfig * config,
				QtTCPServer::CoilDataContainer * coilData,
				QtTCPServer::DiscreteInputDataContainer * discreteInputData,
				QtTCPServer::HoldingRegisterDataContainer * holdingRegisterData,
				QtTCPServer::InputRegisterDataContainer * inputRegisterData,
				QObject * parent = nullptr);

	protected:
		int slaveId() const override;

		void configureConnection() override;

	private:
		struct Members
		{
			TCPServerConfig * config;
		};

		MPtr<Members> m;
};

}
}
}

#endif
