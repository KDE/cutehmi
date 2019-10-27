#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTSERVERMIXIN_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTSERVERMIXIN_HPP

#include "common.hpp"

#include <QtGlobal>

#include <QModbusDataUnitMap>

namespace cutehmi {
namespace modbus {
namespace internal {

template <typename DERIVED>
class QtServerMixin
{
	protected:
		bool setMap(const QModbusDataUnitMap & map);

		bool readData(QModbusDataUnit * newData) const;

		bool writeData(const QModbusDataUnit & newData);

	private:
		const DERIVED & derived() const;

		DERIVED & derived();
};

template <typename DERIVED>
bool QtServerMixin<DERIVED>::setMap(const QModbusDataUnitMap & map)
{
	Q_UNUSED(map)

	// Data containers cover whole address range.

	return true;
}

template<typename DERIVED>
bool QtServerMixin<DERIVED>::readData(QModbusDataUnit * newData) const
{
	//<CuteHMI.Modbus-6.unsolved target="Qt" cause="design">
	// QModbusDataUnit::startAddress() returns `int` value. On systems, where `int` is 16 bit wide it will fail to cover whole
	// Modbus address range (0 - 65535).
	static_assert(std::numeric_limits<quint16>::max() <= static_cast<quint16>(std::numeric_limits<int>::max()), "can not safely use startAddress() function on this system");

	switch (newData->registerType()) {
		case QModbusDataUnit::Coils:
			for (quint16 index = 0, address = static_cast<quint16>(newData->startAddress()); index < static_cast<quint16>(newData->valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-7.workaround target="Qt" cause="design">
				// QModbusDataUnit::setValue() function accepts `int` type as its `index` parameter. It should be however safe to
				// cast `quint16` to `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				newData->setValue(static_cast<int>(index), derived().m->coilData->value(address)->value());
				//</CuteHMI.Modbus-7.workaround>
			}
			break;
		case QModbusDataUnit::DiscreteInputs:
			for (quint16 index = 0, address = static_cast<quint16>(newData->startAddress()); index < static_cast<quint16>(newData->valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-7.workaround target="Qt" cause="design">
				// QModbusDataUnit::setValue() function accepts `int` type as its `index` parameter. It should be however safe to
				// cast `quint16` to `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				newData->setValue(static_cast<int>(index), derived().m->discreteInputData->value(address)->value());
				//</CuteHMI.Modbus-7.workaround>
			}
			break;
		case QModbusDataUnit::HoldingRegisters:
			for (quint16 index = 0, address = static_cast<quint16>(newData->startAddress()); index < static_cast<quint16>(newData->valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-7.workaround target="Qt" cause="design">
				// QModbusDataUnit::setValue() function accepts `int` type as its `index` parameter. It should be however safe to
				// cast `quint16` to `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				newData->setValue(static_cast<int>(index), derived().m->holdingRegisterData->value(address)->value());
				//</CuteHMI.Modbus-7.workaround>
			}
			break;
		case QModbusDataUnit::InputRegisters:
			for (quint16 index = 0, address = static_cast<quint16>(newData->startAddress()); index < static_cast<quint16>(newData->valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-7.workaround target="Qt" cause="design">
				// QModbusDataUnit::setValue() function accepts `int` type as its `index` parameter. It should be however safe to
				// cast `quint16` to `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				newData->setValue(static_cast<int>(index), derived().m->inputRegisterData->value(address)->value());
				//</CuteHMI.Modbus-7.workaround>
			}
			break;
		default:
			CUTEHMI_WARNING("Unrecognized register type '" << newData->registerType() << "'.");
	}
	return true;

	//</CuteHMI.Modbus-6.unsolved>
}

template<typename DERIVED>
bool QtServerMixin<DERIVED>::writeData(const QModbusDataUnit & newData)
{
	//<CuteHMI.Modbus-6.unsolved target="Qt" cause="design">
	// QModbusDataUnit::startAddress() returns `int` value. On systems, where `int` is 16 bit wide it will fail to cover
	// whole Modbus address range (0 - 65535).
	static_assert(std::numeric_limits<quint16>::max() <= static_cast<quint16>(std::numeric_limits<int>::max()), "can not safely use startAddress() function on this system");

	switch (newData.registerType()) {
		case QModbusDataUnit::Coils:
			for (quint16 index = 0, address = static_cast<quint16>(newData.startAddress()); index < static_cast<quint16>(newData.valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-3.workaround target="Qt" cause="design">
				// QModbusDataUnit::value() function accepts `int` type as its `index` parameter. It should be however safe to cast `quint16` to
				// `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				derived().m->coilData->value(address)->setValue(static_cast<bool>(newData.value(static_cast<int>(index))));
				//</CuteHMI.Modbus-3.workaround>
			}
			break;
		case QModbusDataUnit::DiscreteInputs:
			for (quint16 index = 0, address = static_cast<quint16>(newData.startAddress()); index < static_cast<quint16>(newData.valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-3.workaround target="Qt" cause="design">
				// QModbusDataUnit::value() function accepts `int` type as its `index` parameter. It should be however safe to cast `quint16` to
				// `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				derived().m->discreteInputData->value(address)->setValue(static_cast<bool>(newData.value(static_cast<int>(index))));
				//</CuteHMI.Modbus-3.workaround>
			}
			break;
		case QModbusDataUnit::HoldingRegisters:
			for (quint16 index = 0, address = static_cast<quint16>(newData.startAddress()); index < static_cast<quint16>(newData.valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-3.workaround target="Qt" cause="design">
				// QModbusDataUnit::value() function accepts `int` type as its `index` parameter. It should be however safe to cast `quint16` to
				// `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				derived().m->holdingRegisterData->value(address)->setValue(newData.value(static_cast<int>(index)));
				//</CuteHMI.Modbus-3.workaround>
			}
			break;
		case QModbusDataUnit::InputRegisters:
			for (quint16 index = 0, address = static_cast<quint16>(newData.startAddress()); index < static_cast<quint16>(newData.valueCount()); index++, address++)	{ // Note: `uint` returned by valueCount() is guaranteed to be at least 16 bit wide.
				//<CuteHMI.Modbus-3.workaround target="Qt" cause="design">
				// QModbusDataUnit::value() function accepts `int` type as its `index` parameter. It should be however safe to cast `quint16` to
				// `int` here, even if `int` is 16 bit wide, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
				derived().m->inputRegisterData->value(address)->setValue(newData.value(static_cast<int>(index)));
				//</CuteHMI.Modbus-3.workaround>
			}
			break;
		default:
			CUTEHMI_WARNING("Unrecognized register type '" << newData.registerType() << "'.");
	}

	//</CuteHMI.Modbus-6.unsolved>

	//<CuteHMI.Modbus-5.unsolved target="Qt" cause="design">
	// Signal QModbusServer::dataWritten() uses `int` for `address` type. On systems, where `int` is 16 bit wide it will fail to
	// cover whole Modbus address range (0-65535).
	static_assert(std::numeric_limits<quint16>::max() <= static_cast<quint16>(std::numeric_limits<int>::max()), "can not safely use dataWritten() signal on this system");

	//<CuteHMI.Modbus-9.workaround target="Qt" cause="design">
	// QModbusDataUnit::dataWritten() signal accepts `int` type as its `size` parameter, while QModbusDataUnit::valueCount() uses
	// `uint` as return type. As such it is incompatible with `size` parameter, which might not be able to represent all returned
	// values. It should be safe however to cas it to `int`, because of @ref cutehmi::modbus::AbstractDevice-query_limits.
	emit derived().dataWritten(newData.registerType(), newData.startAddress(), static_cast<int>(newData.valueCount()));
	//</CuteHMI.Modbus-9.workaround>

	//</CuteHMI.Modbus-5.unsolved>

	return true;
}

template <typename DERIVED>
const DERIVED & QtServerMixin<DERIVED>::derived() const
{
	return static_cast<const DERIVED &>(*this);
}

template <typename DERIVED>
DERIVED & QtServerMixin<DERIVED>::derived()
{
	return static_cast<DERIVED &>(*this);
}


}
}
}

#endif

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
