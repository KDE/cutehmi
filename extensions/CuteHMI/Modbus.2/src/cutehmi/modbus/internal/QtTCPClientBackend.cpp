#include <cutehmi/modbus/internal/QtTCPClientBackend.hpp>

#include <QModbusTcpClient>

namespace cutehmi {
namespace modbus {
namespace internal {

QtTCPClientBackend::QtTCPClientBackend(TCPClientConfig * config, QObject * parent):
	QtClientBackend(std::make_unique<QModbusTcpClient>(), parent),
	m(new Members(config))
{
}

int QtTCPClientBackend::slaveAddress() const
{
	return m->config->slaveAddress();
}

void QtTCPClientBackend::configureConnection()
{
	qClient()->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m->config->host());
	qClient()->setConnectionParameter(QModbusDevice::NetworkPortParameter, m->config->port());

	CUTEHMI_DEBUG("Client configured on '" << m->config->host() << ":" << m->config->port() << "'.");
}

}
}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
