#include <cutehmi/modbus/internal/QtServerBackend.hpp>

#include <QThread>

namespace cutehmi {
namespace modbus {
namespace internal {

void QtServerBackend::ensureClosed()
{
	if (m->qServer->state() != QModbusDevice::UnconnectedState && m->qServer->state() != QModbusDevice::ClosingState)
		close();
}

QtServerBackend::QtServerBackend(std::unique_ptr<QModbusServer> qServer, QObject * parent):
	AbstractServerBackend(parent),
	m(new Members{qServer.release()})
{
	m->qServer->setParent(this);
	connect(m->qServer, & QModbusServer::stateChanged, this, & QtServerBackend::onStateChanged);
	connect(m->qServer, & QModbusServer::errorOccurred, this, & QtServerBackend::onErrorOccurred);
	connect(m->qServer, & QModbusServer::dataWritten, this, & QtServerBackend::onDataWritten);
}

QModbusServer * QtServerBackend::qServer() const
{
	return m->qServer;
}

bool QtServerBackend::proceedRequest(QUuid requestId)
{
	Q_UNUSED(requestId)

	return true;
}

void QtServerBackend::readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit dataUnit(QModbusDataUnit::Coils, startAddress, endAddress - startAddress + 1);
	readDataUnitBool(requestId, dataUnit);
}

void QtServerBackend::writeCoil(QUuid requestId, quint16 address, bool value)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-2.workaround target="Qt" cause="design">
	// QModbusServer::setData() uses 'quint16' as 'address' parameter, which makes it impossible to cover extended address
	// space of Modbus with 65536 registers (https://en.wikipedia.org/wiki/Modbus). Workaround is to use QModbusServer::setData()
	// overload, which uses QModbusDataUnit as a parameter type.

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(address <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::Coils, address, QVector<quint16> {value}));
	//</CuteHMI.Modbus-4.unsolved>

	//</CuteHMI.Modbus-2.workaround>
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(startAddress <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::Coils, startAddress, values));
	//</CuteHMI.Modbus-4.unsolved>

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit dataUnit(QModbusDataUnit::DiscreteInputs, startAddress, endAddress - startAddress + 1);
	readDataUnitBool(requestId, dataUnit);
}

void QtServerBackend::writeDiscreteInput(QUuid requestId, quint16 address, bool value)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-2.workaround target="Qt" cause="design">
	// QModbusServer::setData() uses 'quint16' as 'address' parameter, which makes it impossible to cover extended address
	// space of Modbus with 65536 registers (https://en.wikipedia.org/wiki/Modbus). Workaround is to use QModbusServer::setData()
	// overload, which uses QModbusDataUnit as a parameter type.

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(address <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::DiscreteInputs, address, QVector<quint16> {value}));
	//</CuteHMI.Modbus-4.unsolved>

	//</CuteHMI.Modbus-2.workaround>
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::writeMultipleDiscreteInputs(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(startAddress <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::DiscreteInputs, startAddress, values));
	//</CuteHMI.Modbus-4.unsolved>

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit dataUnit(QModbusDataUnit::HoldingRegisters, startAddress, endAddress - startAddress + 1);
	readDataUnitInt(requestId, dataUnit);
}

void QtServerBackend::writeHoldingRegister(QUuid requestId, quint16 address, quint16 value)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-2.workaround target="Qt" cause="design">
	// QModbusServer::setData() uses 'quint16' as 'address' parameter, which makes it impossible to cover extended address
	// space of Modbus with 65536 registers (https://en.wikipedia.org/wiki/Modbus). Workaround is to use QModbusServer::setData()
	// overload, which uses QModbusDataUnit as a parameter type.

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(address <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, address, QVector<quint16> {value}));
	//</CuteHMI.Modbus-4.unsolved>

	//</CuteHMI.Modbus-2.workaround>
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(startAddress <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, startAddress, values));
	//</CuteHMI.Modbus-4.unsolved>

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit dataUnit(QModbusDataUnit::InputRegisters, startAddress, endAddress - startAddress + 1);
	readDataUnitInt(requestId, dataUnit);
}

void QtServerBackend::writeInputRegister(QUuid requestId, quint16 address, quint16 value)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-2.workaround target="Qt" cause="design">
	// QModbusServer::setData() uses 'quint16' as 'address' parameter, which makes it impossible to cover extended address
	// space of Modbus with 65536 registers (https://en.wikipedia.org/wiki/Modbus). Workaround is to use QModbusServer::setData()
	// overload, which uses QModbusDataUnit as a parameter type.

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(address <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::InputRegisters, address, QVector<quint16> {value}));
	//</CuteHMI.Modbus-4.unsolved>

	//</CuteHMI.Modbus-2.workaround>
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::writeMultipleInputRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QJsonObject reply;

	//<CuteHMI.Modbus-4.unsolved target="Qt" cause="design">
	// QModbusDataUnit uses `int` for address type. On systems, where `int` is 16 bit wide it will fail to cover whole Modbus
	// address range (0-65535).
	CUTEHMI_ASSERT(startAddress <= static_cast<quint16>(std::numeric_limits<int>::max()), "address too large to be represented on this system");
	m->qServer->setData(QModbusDataUnit(QModbusDataUnit::InputRegisters, startAddress, values));
	//</CuteHMI.Modbus-4.unsolved>

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::open()
{
	if (m->qServer->state() == QModbusDevice::ConnectedState)
		CUTEHMI_DEBUG("Ignoring request - already listening.");
	else if (m->qServer->state() == QModbusDevice::ConnectingState)
		CUTEHMI_DEBUG("Ignoring request - server already attempts to enter listening mode.");
	else if (m->qServer->state() == QModbusDevice::UnconnectedState) {
		// Configure server.
		configureConnection();
		m->qServer->setServerAddress(slaveId());

		if (!m->qServer->connectDevice())
			emit errored(CUTEHMI_ERROR(tr("Failed to initialize listening.")));
	} else {
		if (m->qServer->state() == QModbusDevice::ClosingState) {
			CUTEHMI_WARNING("Request ignored - server is currently proceeding with stop listening operation, which prevents it from initiating listening.");
			emit errored(CUTEHMI_ERROR(tr("Server is currently proceeding with stop listening operation.")));
		} else {
			CUTEHMI_CRITICAL("Request ignored - server is in some unrecognized state, which prevents it from initiating listening.");
			emit errored(CUTEHMI_ERROR(tr("Server is in some unrecognized state, which prevents it from initiating listening.")));
		}
	}
}

void QtServerBackend::close()
{
	if (m->qServer->state() == QModbusDevice::UnconnectedState) {
		CUTEHMI_DEBUG("Server already not listening.");
	} else if (m->qServer->state() == QModbusDevice::ClosingState)
		CUTEHMI_DEBUG("Ignoring request - server already attempts to leave listening mode.");
	else
		do {
			if (m->qServer->state() == QModbusDevice::ConnectedState) {
				m->qServer->disconnectDevice();
			} else {
				QThread::yieldCurrentThread();
				QCoreApplication::processEvents();
			}
		} while (m->qServer->state() != QModbusDevice::UnconnectedState);
}

void QtServerBackend::setBusy(bool busy)
{
	static constexpr quint16 BUSY_OFF = 0x0000;
	static constexpr quint16 BUSY_ON = 0xffff;

	quint16 busyValue = busy ? BUSY_ON : BUSY_OFF;

	if (m->qServer->value(QModbusServer::DeviceBusy).toInt() != busyValue) {
		m->qServer->setValue(QModbusServer::DeviceBusy, busyValue);
		emit busyUpdated(busy);
	}
}

void QtServerBackend::readDataUnitInt(QUuid requestId, QModbusDataUnit & unit)
{
	QJsonObject reply;

	m->qServer->data(& unit);

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::readDataUnitBool(QUuid requestId, QModbusDataUnit & unit)
{
	QJsonObject reply;

	m->qServer->data(& unit);

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void QtServerBackend::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size)
{
	//<CuteHMI.Modbus-5.unsolved target="Qt" cause="design">
	// Signal QModbusServer::dataWritten() uses `int` for `address` type. On systems, where `int` is 16 bit wide it will fail to
	// cover whole Modbus address range (0-65535).
	static_assert(std::numeric_limits<quint16>::max() <= static_cast<quint16>(std::numeric_limits<int>::max()), "can not safely use dataWritten() signal on this system");

	switch (table) {
		case QModbusDataUnit::Coils:
			//<CuteHMI.Modbus-8.workaround target="Qt" cause="design">
			// Parameter `size` is of type `int`. It should be however safe to cast `int` to `quint16` here, even if `int` is 16 bit
			// wide, because of @ref cutehmi-modbus-AbstractDevice-query_limits.
			emit coilsWritten(static_cast<quint16>(address), static_cast<quint16>(size));
			//</CuteHMI.Modbus-8.workaround>
			break;
		case QModbusDataUnit::DiscreteInputs:
			//<CuteHMI.Modbus-8.workaround target="Qt" cause="design">
			// Parameter `size` is of type `int`. It should be however safe to cast `int` to `quint16` here, even if `int` is 16 bit
			// wide, because of @ref cutehmi-modbus-AbstractDevice-query_limits.
			emit discreteInputsWritten(static_cast<quint16>(address), static_cast<quint16>(size));
			//</CuteHMI.Modbus-8.workaround>
			break;
		case QModbusDataUnit::HoldingRegisters:
			//<CuteHMI.Modbus-8.workaround target="Qt" cause="design">
			// Parameter `size` is of type `int`. It should be however safe to cast `int` to `quint16` here, even if `int` is 16 bit
			// wide, because of @ref cutehmi-modbus-AbstractDevice-query_limits.
			emit holdingRegistersWritten(static_cast<quint16>(address), static_cast<quint16>(size));
			//</CuteHMI.Modbus-8.workaround>
			break;
		case QModbusDataUnit::InputRegisters:
			//<CuteHMI.Modbus-8.workaround target="Qt" cause="design">
			// Parameter `size` is of type `int`. It should be however safe to cast `int` to `quint16` here, even if `int` is 16 bit
			// wide, because of @ref cutehmi-modbus-AbstractDevice-query_limits.
			emit inputRegistersWritten(static_cast<quint16>(address), static_cast<quint16>(size));
			//</CuteHMI.Modbus-8.workaround>
			break;
		default:
			CUTEHMI_WARNING("Unrecognized register type '" << table << "'.");
	}
	//</CuteHMI.Modbus-5.unsolved>
}

void QtServerBackend::onStateChanged(QModbusDevice::State state)
{
	CUTEHMI_DEBUG("Server changed state to: '" << state << "'.");

	switch (state) {
		case QModbusDevice::ConnectingState:
			emit stateChanged(AbstractDevice::OPENING);
			break;
		case QModbusDevice::ConnectedState:
			emit stateChanged(AbstractDevice::OPENED);
			emit opened();
			break;
		case QModbusDevice::ClosingState:
			emit stateChanged(AbstractDevice::CLOSING);
			break;
		case QModbusDevice::UnconnectedState:
			emit stateChanged(AbstractDevice::CLOSED);
			emit closed();
			break;
	}
}

void QtServerBackend::onErrorOccurred(QModbusDevice::Error error)
{
	Q_UNUSED(error)

	emit errored(CUTEHMI_ERROR(m->qServer->errorString()));
}

}
}
}

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
