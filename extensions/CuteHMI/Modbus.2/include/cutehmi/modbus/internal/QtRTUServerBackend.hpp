#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTRTUSERVERBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTRTUSERVERBACKEND_HPP

#include "QtServerBackend.hpp"
#include "RTUServerConfig.hpp"
#include "QtRTUServer.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * TCP server backend.
 */
class CUTEHMI_MODBUS_PRIVATE QtRTUServerBackend:
	public QtServerBackend
{
		Q_OBJECT

	public:
		QtRTUServerBackend(RTUServerConfig * config,
				QtRTUServer::CoilDataContainer * coilData,
				QtRTUServer::DiscreteInputDataContainer * discreteInputData,
				QtRTUServer::HoldingRegisterDataContainer * holdingRegisterData,
				QtRTUServer::InputRegisterDataContainer * inputRegisterData,
				QObject * parent = nullptr);

	protected:
		int slaveId() const override;

		void configureConnection() override;

	private:
		struct Members
		{
			RTUServerConfig * config;
		};

		MPtr<Members> m;
};

}
}
}

#endif
