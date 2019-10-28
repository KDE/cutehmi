#include <cutehmi/modbus/internal/QtRTUServerBackend.hpp>
#include <cutehmi/modbus/internal/functions.hpp>

#include <QThread>
#include <QJsonArray>

namespace cutehmi {
namespace modbus {
namespace internal {

QtRTUServerBackend::QtRTUServerBackend(RTUServerConfig * config,
		QtRTUServer::CoilDataContainer * coilData,
		QtRTUServer::DiscreteInputDataContainer * discreteInputData,
		QtRTUServer::HoldingRegisterDataContainer * holdingRegisterData,
		QtRTUServer::InputRegisterDataContainer * inputRegisterData,
		QObject * parent):
	QtServerBackend(std::make_unique<QtRTUServer>(coilData, discreteInputData, holdingRegisterData, inputRegisterData), parent),
	m(new Members{config})
{
}

int QtRTUServerBackend::slaveId() const
{
	return m->config->slaveAddress();
}

void QtRTUServerBackend::configureConnection()
{
	qServer()->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m->config->port());
	qServer()->setConnectionParameter(QModbusDevice::SerialParityParameter, m->config->parity());
	qServer()->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m->config->baudRate());
	qServer()->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, m->config->dataBits());
	qServer()->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, m->config->stopBits());

	CUTEHMI_DEBUG("Server configured on '" << m->config->port()	<< "', " << m->config->baudRate()
			<< ", " << m->config->parity()
			<< ", " << m->config->dataBits()
			<< ", " << m->config->stopBits()
			<< ".");
}

}
}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
