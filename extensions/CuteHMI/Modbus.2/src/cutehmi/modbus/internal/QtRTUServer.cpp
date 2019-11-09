#include <cutehmi/modbus/internal/QtRTUServer.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

QtRTUServer::QtRTUServer(CoilDataContainer * coilData,
		DiscreteInputDataContainer * discreteInputData,
		HoldingRegisterDataContainer * holdingRegisterData,
		InputRegisterDataContainer * inputRegisterData,
		QObject * parent):
	QModbusRtuSerialSlave(parent),
	m(new Members{coilData, discreteInputData, holdingRegisterData, inputRegisterData})
{
}

bool QtRTUServer::setMap(const QModbusDataUnitMap & map)
{
	return Mixin::setMap(map);
}

bool QtRTUServer::readData(QModbusDataUnit * newData) const
{
	return Mixin::readData(newData);
}

bool QtRTUServer::writeData(const QModbusDataUnit & newData)
{
	return Mixin::writeData(newData);
}

}
}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
