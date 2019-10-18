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

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
