#include <cutehmi/modbus/internal/AbstractDeviceBackend.hpp>

#include <QModbusDevice>

namespace cutehmi {
namespace modbus {
namespace internal {

AbstractDeviceBackend::AbstractDeviceBackend(QObject * parent):
	QObject(parent)
{
	connect(this, & AbstractDeviceBackend::openRequested, this, & AbstractDeviceBackend::open);
	connect(this, & AbstractDeviceBackend::closeRequested, this, & AbstractDeviceBackend::close);
}

void AbstractDeviceBackend::processRequest(QJsonObject request)
{
	QUuid requestId = QUuid::fromString(request.value("id").toString());

	AbstractDevice::Function function = static_cast<AbstractDevice::Function>(request.value("function").toInt());
	QJsonObject payload = request.value("payload").toObject();
	if (proceedRequest(requestId)) {
		CUTEHMI_DEBUG("Processing " << humanFunctionName(function) << " request '" << request << "' ...");
		switch (function) {
			case AbstractDevice::FUNCTION_READ_COILS: {
				quint16 startAddress = static_cast<quint16>(payload.value("address").toDouble());
				quint16 endAddress = startAddress + static_cast<quint16>(payload.value("amount").toDouble()) - 1;
				readCoils(requestId, startAddress, endAddress);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_COIL: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				bool value = payload.value("value").toBool();
				writeCoil(requestId, address, value);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_MULTIPLE_COILS: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				QJsonArray valuesArray = payload.value("values").toArray();
				QVector<quint16> values;
				for (auto value = valuesArray.begin(); value != valuesArray.end(); ++value)
					values.append(value->toBool());
				writeMultipleCoils(requestId, address, values);
				break;
			}
			case AbstractDevice::FUNCTION_READ_DISCRETE_INPUTS: {
				quint16 startAddress = static_cast<quint16>(payload.value("address").toDouble());
				quint16 endAddress = startAddress + static_cast<quint16>(payload.value("amount").toDouble()) - 1;
				readDiscreteInputs(requestId, startAddress, endAddress);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_DISCRETE_INPUT: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				bool value = payload.value("value").toBool();
				writeDiscreteInput(requestId, address, value);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				QJsonArray valuesArray = payload.value("values").toArray();
				QVector<quint16> values;
				for (auto value = valuesArray.begin(); value != valuesArray.end(); ++value)
					values.append(value->toBool());
				writeMultipleDiscreteInputs(requestId, address, values);
				break;
			}
			case AbstractDevice::FUNCTION_READ_HOLDING_REGISTERS: {
				quint16 startAddress = static_cast<quint16>(payload.value("address").toDouble());
				quint16 endAddress = startAddress + static_cast<quint16>(payload.value("amount").toDouble()) - 1;
				readHoldingRegisters(requestId, startAddress, endAddress);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_HOLDING_REGISTER: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				quint16 value = static_cast<quint16>(payload.value("value").toDouble());
				writeHoldingRegister(requestId, address, value);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				QJsonArray valuesArray = payload.value("values").toArray();
				QVector<quint16> values;
				for (auto value = valuesArray.begin(); value != valuesArray.end(); ++value)
					values.append(static_cast<quint16>(value->toDouble()));
				writeMultipleHoldingRegisters(requestId, address, values);
				break;
			}
			case AbstractDevice::FUNCTION_READ_INPUT_REGISTERS: {
				quint16 startAddress = static_cast<quint16>(payload.value("address").toDouble());
				quint16 endAddress = startAddress + static_cast<quint16>(payload.value("amount").toDouble()) - 1;
				readInputRegisters(requestId, startAddress, endAddress);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_INPUT_REGISTER: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				quint16 value = static_cast<quint16>(payload.value("value").toDouble());
				writeInputRegister(requestId, address, value);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				QJsonArray valuesArray = payload.value("values").toArray();
				QVector<quint16> values;
				for (auto value = valuesArray.begin(); value != valuesArray.end(); ++value)
					values.append(static_cast<quint16>(value->toDouble()));
				writeMultipleInputRegisters(requestId, address, values);
				break;
			}
			case AbstractDevice::FUNCTION_READ_EXCEPTION_STATUS:
				readExceptionStatus(requestId);
				break;
			case AbstractDevice::FUNCTION_DIAGNOSTICS: {
				AbstractDevice::DiagnosticsSubfunction subfunction = static_cast<AbstractDevice::DiagnosticsSubfunction>(static_cast<quint16>(payload.value("subfunction").toDouble()));
				quint16 data = static_cast<quint16>(payload.value("data").toDouble());
				diagnostics(requestId, subfunction, data);
				break;
			}
			case AbstractDevice::FUNCTION_FETCH_COMM_EVENT_COUNTER:
				fetchCommEventCounter(requestId);
				break;
			case AbstractDevice::FUNCTION_FETCH_COMM_EVENT_LOG:
				fetchCommEventLog(requestId);
				break;
			case AbstractDevice::FUNCTION_REPORT_SLAVE_ID:
				reportSlaveId(requestId);
				break;
			case AbstractDevice::FUNCTION_READ_FILE_RECORD: {
				QJsonArray subrequests = payload.value("subrequests").toArray();
				quint8 byteCount = static_cast<quint8>(subrequests.count()) * 7; // Each subrequest has 7 octets.
				readFileRecord(requestId, byteCount, subrequests);
				break;
			}
			case AbstractDevice::FUNCTION_WRITE_FILE_RECORD: {
				quint8 byteCount = 0;
				QJsonArray subrequests = payload.value("subrequests").toArray();
				for (int i = 0; i < subrequests.count(); i++)
					// Each subrequest consists of: reference type = 1 byte, file = 2 bytes, address = 2 bytes, amount = 2 bytes, N * values * 2 bytes
					byteCount += 7 + subrequests.at(i).toObject().value("values").toArray().count() * 2;
				writeFileRecord(requestId, byteCount, payload.value("subrequests").toArray());
				break;
			}
			case AbstractDevice::FUNCTION_MASK_WRITE_HOLDING_REGISTER: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				quint16 andMask = static_cast<quint16>(payload.value("andMask").toDouble());
				quint16 orMask = static_cast<quint16>(payload.value("orMask").toDouble());
				maskWriteHoldingRegister(requestId, address, andMask, orMask);
				break;
			}
			case AbstractDevice::FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS: {
				quint16 readStartAddress = static_cast<quint16>(payload.value("readAddress").toDouble());
				quint16 readEndAddress = readStartAddress + static_cast<quint16>(payload.value("amount").toDouble()) - 1;
				quint16 writeAddress = static_cast<quint16>(payload.value("writeAddress").toDouble());
				QJsonArray valuesArray = payload.value("values").toArray();
				QVector<quint16> values;
				for (auto value = valuesArray.begin(); value != valuesArray.end(); ++value)
					values.append(static_cast<quint16>(value->toDouble()));
				readWriteMultipleHoldingRegisters(requestId, readStartAddress, readEndAddress, writeAddress, values);
				break;
			}
			case AbstractDevice::FUNCTION_READ_FIFO_QUEUE: {
				quint16 address = static_cast<quint16>(payload.value("address").toDouble());
				readFIFOQueue(requestId, address);
				break;
			}
			default:
				CUTEHMI_CRITICAL("Unsupported function code '" << function << "'.");
		}
	} else
		CUTEHMI_DEBUG("Device is not ready to process " << humanFunctionName(function) << " request '" << request << "'. ");
}

void AbstractDeviceBackend::readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(endAddress)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeCoil(QUuid requestId, quint16 address, bool value)
{
	Q_UNUSED(address)
	Q_UNUSED(value)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(values)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(endAddress)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeDiscreteInput(QUuid requestId, quint16 address, bool value)
{
	Q_UNUSED(address)
	Q_UNUSED(value)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeMultipleDiscreteInputs(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(values)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(endAddress)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeHoldingRegister(QUuid requestId, quint16 address, quint16 value)
{
	Q_UNUSED(address)
	Q_UNUSED(value)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(values)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(endAddress)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeInputRegister(QUuid requestId, quint16 address, quint16 value)
{
	Q_UNUSED(address)
	Q_UNUSED(value)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeMultipleInputRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	Q_UNUSED(startAddress)
	Q_UNUSED(values)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::readExceptionStatus(QUuid requestId)
{
	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::diagnostics(QUuid requestId, AbstractDevice::DiagnosticsSubfunction subfunction, quint16 data)
{
	Q_UNUSED(subfunction)
	Q_UNUSED(data)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::fetchCommEventCounter(QUuid requestId)
{
	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::fetchCommEventLog(QUuid requestId)
{
	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::reportSlaveId(QUuid requestId)
{
	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::readFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests)
{
	Q_UNUSED(subrequests)
	Q_UNUSED(byteCount)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::writeFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests)
{
	Q_UNUSED(subrequests)
	Q_UNUSED(byteCount)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::maskWriteHoldingRegister(QUuid requestId, quint16 address, quint16 andMask, quint16 orMask)
{
	Q_UNUSED(address)
	Q_UNUSED(andMask)
	Q_UNUSED(orMask)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::readWriteMultipleHoldingRegisters(QUuid requestId, quint16 readStartAddress, quint16 readEndAddress, quint16 writeAddress, const QVector<quint16> & values)
{
	Q_UNUSED(readStartAddress)
	Q_UNUSED(readEndAddress)
	Q_UNUSED(writeAddress)
	Q_UNUSED(values)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::readFIFOQueue(QUuid requestId, quint16 address)
{
	Q_UNUSED(address)

	replyIllegalFunction(requestId);
}

void AbstractDeviceBackend::replyIllegalFunction(QUuid requestId)
{
	QJsonObject reply;

	reply.insert("error", "Modbus protocol error.");
	reply.insert("errorCode", QModbusDevice::ProtocolError);
	reply.insert("protocolErrorCode", QModbusPdu::IllegalFunction);
	reply.insert("success", false);

	emit replied(requestId, reply);
}

const char * AbstractDeviceBackend::humanFunctionName(AbstractDevice::Function function) const
{
	switch (function) {
		case AbstractDevice::FUNCTION_READ_COILS:
			return "read coils";
		case AbstractDevice::FUNCTION_WRITE_COIL:
			return "write coil";
		case AbstractDevice::FUNCTION_WRITE_MULTIPLE_COILS:
			return "write multiple coils";
		case AbstractDevice::FUNCTION_READ_DISCRETE_INPUTS:
			return "read discrete inputs";
		case AbstractDevice::FUNCTION_WRITE_DISCRETE_INPUT:
			return "write discrete input";
		case AbstractDevice::FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS:
			return "write multiple discrete inputs";
		case AbstractDevice::FUNCTION_READ_HOLDING_REGISTERS:
			return "read holding register";
		case AbstractDevice::FUNCTION_WRITE_HOLDING_REGISTER:
			return "write holding register";
		case AbstractDevice::FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS:
			return "write multiple holding registers";
		case AbstractDevice::FUNCTION_READ_INPUT_REGISTERS:
			return "read input registers";
		case AbstractDevice::FUNCTION_WRITE_INPUT_REGISTER:
			return "write input register";
		case AbstractDevice::FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS:
			return "write multiple input registers";
		case AbstractDevice::FUNCTION_READ_EXCEPTION_STATUS:
			return "read exception status";
		case AbstractDevice::FUNCTION_DIAGNOSTICS:
			return "diagnostics";
		case AbstractDevice::FUNCTION_FETCH_COMM_EVENT_COUNTER:
			return "fetch comm event counter";
		case AbstractDevice::FUNCTION_FETCH_COMM_EVENT_LOG:
			return "fetch comm event log";
		case AbstractDevice::FUNCTION_REPORT_SLAVE_ID:
			return "report slave id";
		case AbstractDevice::FUNCTION_READ_FILE_RECORD:
			return "read file record";
		case AbstractDevice::FUNCTION_WRITE_FILE_RECORD:
			return "write file record";
		case AbstractDevice::FUNCTION_MASK_WRITE_HOLDING_REGISTER:
			return "mask write holding register";
		case AbstractDevice::FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS:
			return "read/write multiple holding registers";
		case AbstractDevice::FUNCTION_READ_FIFO_QUEUE:
			return "read FIFO queue";
		default:
			CUTEHMI_CRITICAL("Unrecognized function code " << function << ".");
			return "unrecognized function name";
	}

}

}
}
}

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
