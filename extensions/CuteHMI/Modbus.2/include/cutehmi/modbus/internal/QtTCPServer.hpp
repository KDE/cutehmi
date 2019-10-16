#ifndef INCLUDECUTEHMIMODBUSINTERNALSERIALBUSTCPSERVER_HPP
#define INCLUDECUTEHMIMODBUSINTERNALSERIALBUSTCPSERVER_HPP

#include "common.hpp"
#include "RegisterTraits.hpp"
#include "QtServerMixin.hpp"

#include <QModbusTcpServer>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Qt SerialBus based TCP server.
 */
class CUTEHMI_MODBUS_PRIVATE QtTCPServer:
	public QModbusTcpServer,
	protected QtServerMixin<QtTCPServer>
{
		Q_OBJECT

		friend class QtServerMixin<QtTCPServer>;
		typedef QtServerMixin<QtTCPServer> Mixin;

	public:
		typedef typename RegisterTraits<Coil>::Container CoilDataContainer;
		typedef typename RegisterTraits<DiscreteInput>::Container DiscreteInputDataContainer;
		typedef typename RegisterTraits<HoldingRegister>::Container HoldingRegisterDataContainer;
		typedef typename RegisterTraits<InputRegister>::Container InputRegisterDataContainer;

		QtTCPServer(CoilDataContainer * coilData,
				DiscreteInputDataContainer * discreteInputData,
				HoldingRegisterDataContainer * holdingRegisterData,
				InputRegisterDataContainer * inputRegisterData,
				QObject * parent = nullptr);

		bool setMap(const QModbusDataUnitMap & map) override;

	protected:
		bool readData(QModbusDataUnit * newData) const override;

		bool writeData(const QModbusDataUnit & newData) override;

	private:
		struct Members {
			CoilDataContainer * coilData;
			DiscreteInputDataContainer * discreteInputData;
			HoldingRegisterDataContainer * holdingRegisterData;
			InputRegisterDataContainer * inputRegisterData;
		};

		MPtr<Members> m;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALSERIALBUSTCPSERVER_HPP
