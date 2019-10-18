#include <cutehmi/modbus/internal/QtRTUClientBackend.hpp>

#include <QModbusRtuSerialMaster>

namespace cutehmi {
namespace modbus {
namespace internal {

QtRTUClientBackend::QtRTUClientBackend(RTUClientConfig * config, QObject * parent):
	QtClientBackend(std::make_unique<QModbusRtuSerialMaster>(), parent),
	m(new Members(config))
{
}

int QtRTUClientBackend::slaveAddress() const
{
	return m->config->slaveAddress();
}

void QtRTUClientBackend::configureConnection()
{
	qClient()->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m->config->port());
	qClient()->setConnectionParameter(QModbusDevice::SerialParityParameter, m->config->parity());
	qClient()->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m->config->baudRate());
	qClient()->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, m->config->dataBits());
	qClient()->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, m->config->stopBits());

	CUTEHMI_DEBUG("Client configured on '" << m->config->port()	<< "', " << m->config->baudRate()
			<< ", " << m->config->parity()
			<< ", " << m->config->dataBits()
			<< ", " << m->config->stopBits()
			<< ".");
}

}
}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
