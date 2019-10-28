#include <cutehmi/modbus/AbstractDevice.hpp>

#include <cutehmi/modbus/Exception.hpp>

#include <QJsonArray>
#include <QDateTime>

namespace cutehmi {
namespace modbus {

constexpr int AbstractDevice::MAX_READ_TCP_COILS;
constexpr int AbstractDevice::MAX_READ_RTU_COILS;
constexpr int AbstractDevice::MAX_WRITE_TCP_COILS;
constexpr int AbstractDevice::MAX_WRITE_RTU_COILS;
constexpr int AbstractDevice::MAX_READ_TCP_DISCRETE_INPUTS;
constexpr int AbstractDevice::MAX_READ_RTU_DISCRETE_INPUTS;
constexpr int AbstractDevice::MAX_READ_TCP_HOLDING_REGISTERS;
constexpr int AbstractDevice::MAX_READ_RTU_HOLDING_REGISTERS;
constexpr int AbstractDevice::MAX_WRITE_TCP_HOLDING_REGISTERS;
constexpr int AbstractDevice::MAX_WRITE_RTU_HOLDING_REGISTERS;
constexpr int AbstractDevice::MAX_READ_TCP_INPUT_REGISTERS;
constexpr int AbstractDevice::MAX_READ_RTU_INPUT_REGISTERS;

constexpr quint16 AbstractDevice::MIN_ADDRESS;
constexpr quint16 AbstractDevice::MAX_ADDRESS;

constexpr int AbstractDevice::INITIAL_MAX_READ_COILS;
constexpr int AbstractDevice::INITIAL_MAX_WRITE_COILS;
constexpr int AbstractDevice::INITIAL_MAX_READ_DISCRETE_INPUTS;
constexpr int AbstractDevice::INITIAL_MAX_WRITE_DISCRETE_INPUTS;
constexpr int AbstractDevice::INITIAL_MAX_READ_HOLDING_REGISTERS;
constexpr int AbstractDevice::INITIAL_MAX_WRITE_HOLDING_REGISTERS;
constexpr int AbstractDevice::INITIAL_MAX_READ_INPUT_REGISTERS;
constexpr int AbstractDevice::INITIAL_MAX_WRITE_INPUT_REGISTERS;
constexpr AbstractDevice::State AbstractDevice::INITIAL_STATE;
constexpr bool AbstractDevice::INITIAL_READY;

AbstractDevice::State AbstractDevice::state() const
{
	return m->state;
}

bool AbstractDevice::ready() const
{
	return m->ready;
}

int AbstractDevice::maxReadCoils() const
{
	return m->maxReadCoils;
}

void AbstractDevice::setMaxReadCoils(int maxReadCoils)
{
	if (m->maxReadCoils != maxReadCoils) {
		m->maxReadCoils = maxReadCoils;
		emit maxReadCoilsChanged();
	}
}

int AbstractDevice::maxWriteCoils() const
{
	return m->maxWriteCoils;
}

void AbstractDevice::setMaxWriteCoils(int maxWriteCoils)
{
	if (m->maxWriteCoils != maxWriteCoils) {
		m->maxWriteCoils = maxWriteCoils;
		emit maxWriteCoilsChanged();
	}
}

int AbstractDevice::maxReadDiscreteInputs() const
{
	return m->maxReadDiscreteInputs;
}

void AbstractDevice::setMaxReadDiscreteInputs(int maxReadDiscreteInputs)
{
	if (m->maxReadDiscreteInputs != maxReadDiscreteInputs) {
		m->maxReadDiscreteInputs = maxReadDiscreteInputs;
		emit maxReadDiscreteInputsChanged();
	}
}

int AbstractDevice::maxWriteDiscreteInputs() const
{
	return m->maxWriteDiscreteInputs;
}

void AbstractDevice::setMaxWriteDiscreteInputs(int maxWriteDiscreteInputs)
{
	if (m->maxWriteDiscreteInputs != maxWriteDiscreteInputs) {
		m->maxWriteDiscreteInputs = maxWriteDiscreteInputs;
		emit maxWriteDiscreteInputsChanged();
	}
}

int AbstractDevice::maxReadHoldingRegisters() const
{
	return m->maxReadHoldingRegisters;
}

void AbstractDevice::setMaxReadHoldingRegisters(int maxReadHoldingRegisters)
{
	if (m->maxReadHoldingRegisters != maxReadHoldingRegisters) {
		m->maxReadHoldingRegisters = maxReadHoldingRegisters;
		emit maxReadHoldingRegistersChanged();
	}
}

int AbstractDevice::maxWriteHoldingRegisters() const
{
	return m->maxWriteHoldingRegisters;
}

void AbstractDevice::setMaxWriteHoldingRegisters(int maxWriteHoldingRegisters)
{
	if (m->maxWriteHoldingRegisters != maxWriteHoldingRegisters) {
		m->maxWriteHoldingRegisters = maxWriteHoldingRegisters;
		emit maxWriteHoldingRegistersChanged();
	}
}

int AbstractDevice::maxReadInputRegisters() const
{
	return m->maxReadInputRegisters;
}

void AbstractDevice::setMaxReadInputRegisters(int maxReadInputRegisters)
{
	if (m->maxReadInputRegisters != maxReadInputRegisters) {
		m->maxReadInputRegisters = maxReadInputRegisters;
		emit maxReadInputRegistersChanged();
	}
}

int AbstractDevice::maxWriteInputRegisters() const
{
	return m->maxWriteInputRegisters;
}

void AbstractDevice::setMaxWriteInputRegisters(int maxWriteInputRegisters)
{
	if (m->maxWriteInputRegisters != maxWriteInputRegisters) {
		m->maxWriteInputRegisters = maxWriteInputRegisters;
		emit maxWriteInputRegistersChanged();
	}
}

Coil * AbstractDevice::coilAt(quint16 address)
{
	return coilData().value(address);
}

DiscreteInput * AbstractDevice::discreteInputAt(quint16 address)
{
	return discreteInputData().value(address);
}

HoldingRegister * AbstractDevice::holdingRegisterAt(quint16 address)
{
	return holdingRegisterData().value(address);
}

InputRegister * AbstractDevice::inputRegisterAt(quint16 address)
{
	return inputRegisterData().value(address);
}

void AbstractDevice::requestReadCoils(quint16 address, quint16 amount, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("amount", static_cast<double>(amount));
	request(FUNCTION_READ_COILS, payload, requestId);
}

void AbstractDevice::requestWriteCoil(quint16 address, bool value, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("value", value);
	request(FUNCTION_WRITE_COIL, payload, requestId);
}

void AbstractDevice::requestWriteMultipleCoils(quint16 address, QJsonArray values, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("values", values);
	request(FUNCTION_WRITE_MULTIPLE_COILS, payload, requestId);
}

void AbstractDevice::requestReadDiscreteInputs(quint16 address, quint16 amount, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("amount", static_cast<double>(amount));
	request(FUNCTION_READ_DISCRETE_INPUTS, payload, requestId);
}

void AbstractDevice::requestWriteDiscreteInput(quint16 address, bool value, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("value", value);
	request(FUNCTION_WRITE_DISCRETE_INPUT, payload, requestId);
}

void AbstractDevice::requestWriteMultipleDiscreteInputs(quint16 address, QJsonArray values, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("values", values);
	request(FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS, payload, requestId);
}

void AbstractDevice::requestReadHoldingRegisters(quint16 address, quint16 amount, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("amount", static_cast<double>(amount));
	request(FUNCTION_READ_HOLDING_REGISTERS, payload, requestId);
}

void AbstractDevice::requestWriteHoldingRegister(quint16 address, quint16 value, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("value", static_cast<double>(value));
	request(FUNCTION_WRITE_HOLDING_REGISTER, payload, requestId);
}

void AbstractDevice::requestWriteMultipleHoldingRegisters(quint16 address, QJsonArray values, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("values", values);
	request(FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS, payload, requestId);
}

void AbstractDevice::requestReadInputRegisters(quint16 address, quint16 amount, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("amount", static_cast<double>(amount));
	request(FUNCTION_READ_INPUT_REGISTERS, payload, requestId);
}

void AbstractDevice::requestWriteInputRegister(quint16 address, quint16 value, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("value", static_cast<double>(value));
	request(FUNCTION_WRITE_INPUT_REGISTER, payload, requestId);
}

void AbstractDevice::requestWriteMultipleInputRegisters(quint16 address, QJsonArray values, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("values", values);
	request(FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS, payload, requestId);
}

void AbstractDevice::requestDiagnostics(AbstractDevice::DiagnosticsSubfunction subfunction, quint16 data, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("subfunction", static_cast<double>(subfunction));
	payload.insert("data", data);
	request(FUNCTION_DIAGNOSTICS, payload, requestId);
}

void AbstractDevice::requestReadExceptionStatus(QUuid * requestId)
{
	QJsonObject payload;
	request(FUNCTION_READ_EXCEPTION_STATUS, payload, requestId);
}

void AbstractDevice::requestFetchCommEventCounter(QUuid * requestId)
{
	QJsonObject payload;
	request(FUNCTION_FETCH_COMM_EVENT_COUNTER, payload, requestId);
}

void AbstractDevice::requestFetchCommEventLog(QUuid * requestId)
{
	QJsonObject payload;
	request(FUNCTION_FETCH_COMM_EVENT_LOG, payload, requestId);
}

void AbstractDevice::requestReportSlaveId(QUuid * requestId)
{
	QJsonObject payload;
	request(FUNCTION_REPORT_SLAVE_ID, payload, requestId);
}

void AbstractDevice::requestMaskWriteHoldingRegister(quint16 address, quint16 andMask, quint16 orMask, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	payload.insert("andMask", static_cast<double>(andMask));
	payload.insert("orMask", static_cast<double>(orMask));
	request(FUNCTION_MASK_WRITE_HOLDING_REGISTER, payload, requestId);
}

void AbstractDevice::requestReadWriteMultipleHoldingRegisters(quint16 readAddress, quint16 amount, quint16 writeAddress, QJsonArray values, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("readAddress", static_cast<double>(readAddress));
	payload.insert("amount", static_cast<double>(amount));
	payload.insert("writeAddress", static_cast<double>(writeAddress));
	payload.insert("values", values);
	request(FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS, payload, requestId);
}

void AbstractDevice::requestReadFIFOQueue(quint16 address, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("address", static_cast<double>(address));
	request(FUNCTION_READ_FIFO_QUEUE, payload, requestId);
}

QJsonObject AbstractDevice::readFileRecordSubrequest(quint16 file, quint16 address, quint16 amount)
{
	QJsonObject subrequest;
	subrequest.insert("referenceType", 0x06);	// "must be specified as 6" -- "Modicon Modbus Protocol Reference Guide PI–MBUS–300  Rev. J"
	subrequest.insert("file", static_cast<double>(file));
	subrequest.insert("address", static_cast<double>(address));
	subrequest.insert("amount", static_cast<double>(amount));
	return subrequest;
}

void AbstractDevice::requestReadFileRecord(QJsonArray subrequests, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("subrequests", subrequests);
	request(FUNCTION_READ_FILE_RECORD, payload, requestId);
}

QJsonObject AbstractDevice::writeFileRecordSubrequest(quint16 file, quint16 address, QJsonArray values)
{
	QJsonObject subrequest;
	subrequest.insert("referenceType", 0x06);	// "must be specified as 6" -- "Modicon Modbus Protocol Reference Guide PI–MBUS–300  Rev. J"
	subrequest.insert("file", static_cast<double>(file));
	subrequest.insert("address", static_cast<double>(address));
	subrequest.insert("values", values);
	return subrequest;
}

void AbstractDevice::requestWriteFileRecord(QJsonArray subrequests, QUuid * requestId)
{
	QJsonObject payload;
	payload.insert("subrequests", subrequests);
	request(FUNCTION_WRITE_FILE_RECORD, payload, requestId);
}

void AbstractDevice::request(Function function, QJsonObject payload, QUuid * requestId)
{
	QJsonObject request;

	if (requestId != nullptr) {
		*requestId = QUuid::createUuid();
		request.insert("id", requestId->toString());
	} else
		request.insert("id", QUuid::createUuid().toString());

	request.insert("function", function);

	request.insert("payload", payload);

	// QJsonValue is converting qint64 to IEEE 754 double, which can directly represent integers up to 2^53, but it should still last till year 285410...
	request.insert("timestamp", QDateTime::currentMSecsSinceEpoch());

	CUTEHMI_DEBUG("Received request '" << request << "'.");

	if (validateRequest(request)) {
		m->pendingRequests.append(request);
		handleRequest(request);
	}
}

AbstractDevice::AbstractDevice(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

AbstractDevice::~AbstractDevice()
{
	m->coils.free();
	m->discreteInputs.free();
	m->holdingRegisters.free();
	m->inputRegisters.free();
}

const AbstractDevice::CoilDataContainer & AbstractDevice::coilData() const
{
	return m->coils;
}

AbstractDevice::CoilDataContainer & AbstractDevice::coilData()
{
	return m->coils;
}

const AbstractDevice::DiscreteInputDataContainer & AbstractDevice::discreteInputData() const
{
	return m->discreteInputs;
}

AbstractDevice::DiscreteInputDataContainer & AbstractDevice::discreteInputData()
{
	return m->discreteInputs;
}

const AbstractDevice::HoldingRegisterDataContainer & AbstractDevice::holdingRegisterData() const
{
	return m->holdingRegisters;
}

AbstractDevice::HoldingRegisterDataContainer & AbstractDevice::holdingRegisterData()
{
	return m->holdingRegisters;
}

const AbstractDevice::InputRegisterDataContainer & AbstractDevice::inputRegisterData() const
{
	return m->inputRegisters;
}

AbstractDevice::InputRegisterDataContainer & AbstractDevice::inputRegisterData()
{
	return m->inputRegisters;
}

QJsonObject AbstractDevice::pendingRequest(QUuid requestId) const
{
	for (auto it = m->pendingRequests.begin(); it != m->pendingRequests.end(); ++it)
		if (QUuid::fromString(it->value("id").toString()) == requestId)
			return *it;
	return QJsonObject();
}

QJsonObject AbstractDevice::takePendingRequest(QUuid requestId)
{
	for (auto it = m->pendingRequests.begin(); it != m->pendingRequests.end(); ++it)
		if (QUuid::fromString(it->value("id").toString()) == requestId) {
			QJsonObject result = *it;
			m->pendingRequests.erase(it);
			return result;
		}
	return QJsonObject();
}

void AbstractDevice::handleReply(QUuid requestId, QJsonObject reply)
{
	QJsonObject request = takePendingRequest(requestId);
	if (request.isEmpty()) {
		CUTEHMI_CRITICAL("Could not find a record in pending requests for the request '" << requestId << "'.");
		return;
	}

	qint64 elapsedTime = QDateTime::currentMSecsSinceEpoch() - qRound64(request.value("timestamp").toDouble());

	CUTEHMI_DEBUG("Handling reply '" << reply << "' to request '" << requestId << "', which took " << elapsedTime << " [ms] to complete.");

	if (validateReply(request, reply)) {
		if (!reply.value("success").toBool()) {
			CUTEHMI_WARNING("Request '" << requestId << "' failed.");
		} else {
			Function function = static_cast<Function>(request.value("function").toInt());
			switch (function) {
				case FUNCTION_READ_COILS: {
					quint16 address = static_cast<quint16>(request.value("payload").toObject().value("address").toDouble());
					// If reply contains values, write them down to data container, otherwise assume containers have been already updated.
					if (reply.contains("values")) {
						QJsonArray values = reply.value("values").toArray();
						for (auto valueIt = values.begin(); valueIt != values.end(); ++valueIt) {
							coilData().value(address)->setValue(valueIt->toBool());
							address++;
						}
					}
					break;
				}
				case FUNCTION_WRITE_COIL:
					break;
				case FUNCTION_WRITE_MULTIPLE_COILS:
					break;
				case FUNCTION_READ_DISCRETE_INPUTS: {
					quint16 address = static_cast<quint16>(request.value("payload").toObject().value("address").toDouble());
					// If reply contains values, write them down to data container, otherwise assume containers have been already updated.
					if (reply.contains("values")) {
						QJsonArray values = reply.value("values").toArray();
						for (auto valueIt = values.begin(); valueIt != values.end(); ++valueIt) {
							discreteInputData().value(address)->setValue(valueIt->toBool());
							address++;
						}
					}
					break;
				}
				case FUNCTION_WRITE_DISCRETE_INPUT:
					break;
				case FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS:
					break;
				case FUNCTION_READ_HOLDING_REGISTERS: {
					quint16 address = static_cast<quint16>(request.value("payload").toObject().value("address").toDouble());
					// If reply contains values, write them down to data container, otherwise assume containers have been already updated.
					if (reply.contains("values")) {
						QJsonArray values = reply.value("values").toArray();
						for (auto valueIt = values.begin(); valueIt != values.end(); ++valueIt) {
							holdingRegisterData().value(address)->setValue(static_cast<quint16>(valueIt->toDouble()));
							address++;
						}
					}
					break;
				}
				case FUNCTION_WRITE_HOLDING_REGISTER:
					break;
				case FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS:
					break;
				case FUNCTION_READ_INPUT_REGISTERS: {
					quint16 address = static_cast<quint16>(request.value("payload").toObject().value("address").toDouble());
					// If reply contains values, write them down to data container, otherwise assume containers have been already updated.
					if (reply.contains("values")) {
						QJsonArray values = reply.value("values").toArray();
						for (auto valueIt = values.begin(); valueIt != values.end(); ++valueIt) {
							inputRegisterData().value(address)->setValue(static_cast<quint16>(valueIt->toDouble()));
							address++;
						}
					}
					break;
				}
				case FUNCTION_WRITE_INPUT_REGISTER:
					break;
				case FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS:
					break;
				case FUNCTION_READ_EXCEPTION_STATUS:
					break;
				case FUNCTION_DIAGNOSTICS:
					break;
				case FUNCTION_FETCH_COMM_EVENT_COUNTER:
					break;
				case FUNCTION_FETCH_COMM_EVENT_LOG:
					break;
				case FUNCTION_REPORT_SLAVE_ID:
					break;
				case FUNCTION_READ_FILE_RECORD:
					break;
				case FUNCTION_WRITE_FILE_RECORD:
					break;
				case FUNCTION_MASK_WRITE_HOLDING_REGISTER:
					break;
				case FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS: {
					quint16 address = static_cast<quint16>(request.value("payload").toObject().value("address").toDouble());
					// If reply contains values, write them down to data container, otherwise assume containers have been already updated.
					if (reply.contains("values")) {
						QJsonArray values = reply.value("values").toArray();
						for (auto valueIt = values.begin(); valueIt != values.end(); ++valueIt) {
							holdingRegisterData().value(address)->setValue(static_cast<quint16>(valueIt->toDouble()));
							address++;
						}
					}
					break;
				}
				case FUNCTION_READ_FIFO_QUEUE:
					break;
				default:
					CUTEHMI_CRITICAL("Unsupported function code '" << function << "'.");
			}
		}
		emit requestCompleted(request, reply);
	}
}

void AbstractDevice::setState(AbstractDevice::State state)
{
	if (m->state != state) {
		m->state = state;
		emit stateChanged();
	}
}

void AbstractDevice::setReady(bool ready)
{
	if (m->ready != ready) {
		m->ready = ready;
		emit readyChanged();
	}
}

void AbstractDevice::ValidatePayloadAddressKey(const QJsonObject & json, const QString & key)
{
	ValidateNumberKey(json, key, "payload");

	double address = json.value(key).toDouble();
	if ((address < MIN_ADDRESS) || (address > MAX_ADDRESS))
		throw Exception(QString("Value of '%1' in 'payload' is outside of Modbus address range [%2, %3].").arg(key).arg(MIN_ADDRESS).arg(MAX_ADDRESS));
}

void AbstractDevice::ValidatePayloadAmountKey(const QJsonObject & json, int max)
{
	ValidateNumberKey(json, "amount", "payload");

	double amount = json.value("amount").toDouble();
	if ((amount < 0) || (amount > max))
		throw Exception(QString("Value of 'amount' in 'payload' is outside of a range [0, %1].").arg(max));
}

void AbstractDevice::ValidatePayloadValueKeyInt(const QJsonObject & json)
{
	ValidateNumberKey(json, "value", "payload");

	static constexpr quint16 MIN = std::numeric_limits<quint16>::min();
	static constexpr quint16 MAX = std::numeric_limits<quint16>::max();
	double value = json.value("value").toDouble();
	if ((value < MIN) || (value > MAX))
		throw Exception(QString("Value of 'value' in 'payload' is outside of a 16 bit unsigned integer range [%1, %2].").arg(MIN).arg(MAX));
}

void AbstractDevice::ValidatetPayloadValueKeyBool(const QJsonObject & json)
{
	ValidateBoolKey(json, "value", "payload");
}

void AbstractDevice::ValidatePayloadReadFileRecordSubrequestsKey(const QJsonObject & json)
{
	ValidateArrayKey(json, "subrequests", "payload");

	QJsonArray array = json.value("subrequests").toArray();
	for (int i = 0; i < array.size(); i++) {
		if (!array.at(i).isObject())
			throw Exception(QString("Array element 'subrequests[%1]' in 'payload' is not an object.").arg(i));

		QJsonObject subrequest = array.at(i).toObject();

		ValidateNumberKey(subrequest, "referenceType", QString("payload.subrequests[%1]").arg(i));
		double referenceType = subrequest.value("referenceType").toDouble();
		static constexpr quint16 REFERENCE_TYPE = 0x06;	// Constant value according to MODBUS Application Protocol Specification V1.1b [6.14].
		if (referenceType != REFERENCE_TYPE)
			throw Exception(QString("Value of 'referenceType' in 'payload.subrequests[%1]' must be %2.").arg(i).arg(REFERENCE_TYPE));

		ValidateNumberKey(subrequest, "file", QString("payload.subrequests[%1]").arg(i));
		static constexpr quint16 FILE_MIN = 0x0001;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		static constexpr quint16 FILE_MAX = 0xFFFF;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		double file = subrequest.value("file").toDouble();
		if ((file < FILE_MIN) || (file > FILE_MAX))
			throw Exception(QString("Value of 'file' in 'payload.subrequests[%1]' outside of a range defined by the protocol [%2, %3].").arg(i).arg(FILE_MIN).arg(FILE_MAX));

		ValidateNumberKey(subrequest, "address", QString("payload.subrequests[%1]").arg(i));
		static constexpr quint16 ADDRESS_MIN = 0x0000;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		static constexpr quint16 ADDRESS_MAX = 0x270F;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		double address = subrequest.value("address").toDouble();
		if ((address < ADDRESS_MIN) || (address > ADDRESS_MAX))
			throw Exception(QString("Value of 'address' in 'payload.subrequests[%1]' outside of a range defined by the protocol [%2, %3].").arg(i).arg(ADDRESS_MIN).arg(ADDRESS_MAX));

		ValidateNumberKey(subrequest, "amount", QString("payload.subrequests[%1]").arg(i));
	}
}

void AbstractDevice::ValidatePayloadWriteFileRecordSubrequestsKey(const QJsonObject & json)
{
	ValidateArrayKey(json, "subrequests", "payload");

	QJsonArray array = json.value("subrequests").toArray();
	for (int i = 0; i < array.size(); i++) {
		if (!array.at(i).isObject())
			throw Exception(QString("Array element 'subrequests[%1]' in 'payload' is not an object.").arg(i));

		QJsonObject subrequest = array.at(i).toObject();

		ValidateNumberKey(subrequest, "referenceType", QString("payload.subrequests[%1]").arg(i));
		double referenceType = subrequest.value("referenceType").toDouble();
		static constexpr quint16 REFERENCE_TYPE = 0x06;	// Constant value according to MODBUS Application Protocol Specification V1.1b [6.14].
		if (referenceType != REFERENCE_TYPE)
			throw Exception(QString("Value of 'referenceType' in 'payload.subrequests[%1]' must be %2.").arg(i).arg(REFERENCE_TYPE));

		ValidateNumberKey(subrequest, "file", QString("payload.subrequests[%1]").arg(i));
		static constexpr quint16 FILE_MIN = 0x0001;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		static constexpr quint16 FILE_MAX = 0xFFFF;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		double file = subrequest.value("file").toDouble();
		if ((file < FILE_MIN) || (file > FILE_MAX))
			throw Exception(QString("Value of 'file' in 'payload.subrequests[%1]' outside of a range defined by the protocol [%2, %3].").arg(i).arg(FILE_MIN).arg(FILE_MAX));

		ValidateNumberKey(subrequest, "address", QString("payload.subrequests[%1]").arg(i));
		static constexpr quint16 ADDRESS_MIN = 0x0000;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		static constexpr quint16 ADDRESS_MAX = 0x270F;	// According to MODBUS Application Protocol Specification V1.1b [6.14].
		double address = subrequest.value("address").toDouble();
		if ((address < ADDRESS_MIN) || (address > ADDRESS_MAX))
			throw Exception(QString("Value of 'address' in 'payload.subrequests[%1]' outside of a range defined by the protocol [%2, %3].").arg(i).arg(ADDRESS_MIN).arg(ADDRESS_MAX));

		ValidateNumberArrayKey(subrequest, "values", QString("payload.subrequests[%1]").arg(i));
	}
}

void AbstractDevice::ValidateBoolKey(const QJsonObject & json, const QString & key, const QString & path)
{
	QString where;
	if (!path.isEmpty())
		where = QString(" in '") + path + "'";

	if (!json.contains(key))
		throw Exception(QString("Missing '%1'%2 key.").arg(key).arg(where));

	if (!json.value(key).isBool())
		throw Exception(QString("Value of '%1'%2 in is not a Boolean.").arg(key).arg(where));
}

void AbstractDevice::ValidateNumberKey(const QJsonObject & json, const QString & key, const QString & path)
{
	QString where;
	if (!path.isEmpty())
		where = QString(" in '") + path + "'";

	if (!json.contains(key))
		throw Exception(QString("Missing '%1' key%2.").arg(key).arg(where));

	if (!json.value(key).isDouble())
		throw Exception(QString("Value of '%1'%2 is not a number.").arg(key).arg(where));
}

void AbstractDevice::ValidateArrayKey(const QJsonObject & json, const QString & key, const QString & path)
{
	QString where;
	if (!path.isEmpty())
		where = QString(" in '") + path + "'";

	if (!json.contains(key))
		throw Exception(QString("Missing '%1' key%2.").arg(key).arg(where));

	if (!json.value(key).isArray())
		throw Exception(QString("Value of '%1'%2 is not an array.").arg(key).arg(where));
}

void AbstractDevice::ValidateNumberArrayKey(const QJsonObject & json, const QString & key, const QString & path)
{
	ValidateArrayKey(json, key, path);

	QString where;
	if (!path.isEmpty())
		where = QString(" in '") + path + "'";

	QJsonArray array = json.value(key).toArray();
	for (int i = 0; i < array.size(); i++)
		if (!array.at(i).isDouble())
			throw Exception(QString("Array element '%1[%2]'%3 is not a number.").arg(key).arg(i).arg(where));
}

void AbstractDevice::ValidateBoolArrayKey(const QJsonObject & json, const QString & key, const QString & path)
{
	ValidateArrayKey(json, key, path);

	QString where;
	if (!path.isEmpty())
		where = QString(" in '") + path + "'";

	QJsonArray array = json.value(key).toArray();
	for (int i = 0; i < array.size(); i++)
		if (!array.at(i).isBool())
			throw Exception(QString("Array element '%1[%2]'%3 is not a Boolean.").arg(key).arg(i).arg(where));
}

void AbstractDevice::ValidateObjectArrayKey(const QJsonObject & json, const QString & key, const QString & path,  std::function<void(const QJsonObject & json, const QString & path)> filter)
{
	ValidateArrayKey(json, key, path);

	QString where;
	if (!path.isEmpty())
		where = QString(" in '") + path + "'";

	QJsonArray array = json.value(key).toArray();
	for (int i = 0; i < array.size(); i++) {
		if (!array.at(i).isObject())
			throw Exception(QString("Array element '%1[%2]'%3 is not an object.").arg(key).arg(i).arg(where));

		if (filter != nullptr) {
			QString subpath = path.isEmpty() ? "" : path + ".";
			filter(array.at(i).toObject(), subpath + key + "[" + QString::number(i) + "]");
		}
	}
}

void AbstractDevice::ValidateReadFileRecordSubresponsesKey(const QJsonObject & json, const QString & path)
{
	ValidateNumberKey(json, "byteCount", path);
	ValidateNumberKey(json, "referenceType", path);
	ValidateNumberArrayKey(json, "values", path);
}

void AbstractDevice::ValidateWriteFileRecordSubresponsesKey(const QJsonObject & json, const QString & path)
{
	ValidateNumberKey(json, "referenceType", path);
	ValidateNumberKey(json, "file", path);
	ValidateNumberKey(json, "address", path);
	ValidateNumberKey(json, "amount", path);
	ValidateNumberArrayKey(json, "values", path);
}

bool AbstractDevice::validateRequest(const QJsonObject & request)
{
	QUuid id = QUuid::fromString(request.value("id").toString());
	try {
		if (id.isNull())
			throw Exception("Request does not have a valid 'id'.");

		Function function;
		if (!request.contains("function"))
			throw Exception(QString("Missing 'function' key."));
		if (!request.value("function").isDouble())
			throw Exception(QString("Value of 'function' is not a number."));
		else
			function = static_cast<Function>(request.value("function").toInt());

		QJsonObject payload;
		if (!request.contains("payload"))
			throw Exception("Missing 'payload' key.");
		if (!request.value("payload").isObject())
			throw Exception("Value of 'payload' is not an object.");
		else
			payload = request.value("payload").toObject();

		switch (function) {
			case FUNCTION_READ_COILS:
				ValidatePayloadAddressKey(payload);
				ValidatePayloadAmountKey(payload, maxReadCoils());
				break;
			case FUNCTION_WRITE_COIL:
				ValidatePayloadAddressKey(payload);
				ValidatetPayloadValueKeyBool(payload);
				break;
			case FUNCTION_WRITE_MULTIPLE_COILS:
				ValidatePayloadAddressKey(payload);
				ValidateBoolArrayKey(payload, "values", "payload");
				break;
			case FUNCTION_READ_DISCRETE_INPUTS:
				ValidatePayloadAddressKey(payload);
				ValidatePayloadAmountKey(payload, maxReadDiscreteInputs());
				break;
			case FUNCTION_WRITE_DISCRETE_INPUT:
				ValidatePayloadAddressKey(payload);
				ValidatetPayloadValueKeyBool(payload);
				break;
			case FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS:
				ValidatePayloadAddressKey(payload);
				ValidateBoolArrayKey(payload, "values", "payload");
				break;
			case FUNCTION_READ_HOLDING_REGISTERS:
				ValidatePayloadAddressKey(payload);
				ValidatePayloadAmountKey(payload, maxReadHoldingRegisters());
				break;
			case FUNCTION_WRITE_HOLDING_REGISTER:
				ValidatePayloadAddressKey(payload);
				ValidatePayloadValueKeyInt(payload);
				break;
			case FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS:
				ValidatePayloadAddressKey(payload);
				ValidateNumberArrayKey(payload, "values", "payload");
				break;
			case FUNCTION_READ_INPUT_REGISTERS:
				ValidatePayloadAddressKey(payload);
				ValidatePayloadAmountKey(payload, maxReadInputRegisters());
				break;
			case FUNCTION_WRITE_INPUT_REGISTER:
				ValidatePayloadAddressKey(payload);
				ValidatePayloadValueKeyInt(payload);
				break;
			case FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS:
				ValidatePayloadAddressKey(payload);
				ValidateNumberArrayKey(payload, "values", "payload");
				break;
			case FUNCTION_READ_EXCEPTION_STATUS:
				break;
			case FUNCTION_DIAGNOSTICS:
				ValidateNumberKey(payload, "subfunction", "payload");
				ValidateNumberKey(payload, "data", "payload");
				break;
			case FUNCTION_FETCH_COMM_EVENT_COUNTER:
				break;
			case FUNCTION_FETCH_COMM_EVENT_LOG:
				break;
			case FUNCTION_REPORT_SLAVE_ID:
				break;
			case FUNCTION_READ_FILE_RECORD:
				ValidatePayloadReadFileRecordSubrequestsKey(payload);
				break;
			case FUNCTION_WRITE_FILE_RECORD:
				ValidatePayloadWriteFileRecordSubrequestsKey(payload);
				break;
			case FUNCTION_MASK_WRITE_HOLDING_REGISTER:
				ValidatePayloadAddressKey(payload);
				ValidateNumberKey(payload, "andMask", "payload");
				ValidateNumberKey(payload, "orMask", "payload");
				break;
			case FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS:
				ValidatePayloadAddressKey(payload, "readAddress");
				ValidatePayloadAmountKey(payload, maxReadHoldingRegisters());
				ValidatePayloadAddressKey(payload, "writeAddress");
				ValidateNumberArrayKey(payload, "values", "payload");
				break;
			case FUNCTION_READ_FIFO_QUEUE:
				ValidatePayloadAddressKey(payload);
				break;
			default:
				CUTEHMI_CRITICAL("Unsupported function code '" << function << "'.");
		}
	} catch (const Exception & e) {
		CUTEHMI_CRITICAL("Request '" << id << "' is illformed. " << e.what());
		return false;
	}
	return true;
}

bool AbstractDevice::validateReply(const QJsonObject & request, const QJsonObject & reply)
{
	QUuid id = QUuid::fromString(request.value("id").toString());

	try {
		Function function = static_cast<Function>(request.value("function").toInt());
		switch (function) {
			case FUNCTION_READ_COILS:
				ValidateBoolKey(reply, "success");
				if (reply.contains("values"))
					ValidateBoolArrayKey(reply, "values");
				break;
			case FUNCTION_WRITE_COIL:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_WRITE_MULTIPLE_COILS:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_READ_DISCRETE_INPUTS:
				ValidateBoolKey(reply, "success");
				if (reply.contains("values"))
					ValidateBoolArrayKey(reply, "values");
				break;
			case FUNCTION_WRITE_DISCRETE_INPUT:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_WRITE_MULTIPLE_DISCRETE_INPUTS:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_READ_HOLDING_REGISTERS:
				ValidateBoolKey(reply, "success");
				if (reply.contains("values"))
					ValidateNumberArrayKey(reply, "values");
				break;
			case FUNCTION_WRITE_HOLDING_REGISTER:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_WRITE_MULTIPLE_HOLDING_REGISTERS:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_READ_INPUT_REGISTERS:
				ValidateBoolKey(reply, "success");
				if (reply.contains("values"))
					ValidateNumberArrayKey(reply, "values");
				break;
			case FUNCTION_WRITE_INPUT_REGISTER:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_WRITE_MULTIPLE_INPUT_REGISTERS:
				ValidateBoolKey(reply, "success");
				break;
			case FUNCTION_READ_EXCEPTION_STATUS:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool())
					ValidateNumberKey(reply, "exceptionStatus");
				break;
			case FUNCTION_DIAGNOSTICS:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "subfunction");
					ValidateNumberKey(reply, "data");
				}
				break;
			case FUNCTION_FETCH_COMM_EVENT_COUNTER:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "eventCount");
					ValidateNumberKey(reply, "status");
				}
				break;
			case FUNCTION_FETCH_COMM_EVENT_LOG:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "byteCount");
					ValidateNumberKey(reply, "status");
					ValidateNumberKey(reply, "eventCount");
					ValidateNumberKey(reply, "messageCount");
					ValidateNumberArrayKey(reply, "events");
				}
				break;
			case FUNCTION_REPORT_SLAVE_ID:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "byteCount");
					ValidateNumberKey(reply, "slaveId");
					ValidateNumberKey(reply, "runIndicatorStatus");
					ValidateNumberArrayKey(reply, "additionalData");
				}
				break;
			case FUNCTION_READ_FILE_RECORD:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "byteCount");
					ValidateObjectArrayKey(reply, "subresponses", "", & AbstractDevice::ValidateReadFileRecordSubresponsesKey);
				}
				break;
			case FUNCTION_WRITE_FILE_RECORD:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "byteCount");
					ValidateObjectArrayKey(reply, "subresponses", "", & AbstractDevice::ValidateWriteFileRecordSubresponsesKey);
				}
				break;
			case FUNCTION_MASK_WRITE_HOLDING_REGISTER:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "address");
					ValidateNumberKey(reply, "andMask");
					ValidateNumberKey(reply, "orMask");
				}
				break;
			case FUNCTION_READ_WRITE_MULTIPLE_HOLDING_REGISTERS:
				ValidateBoolKey(reply, "success");
				if (reply.contains("values"))
					ValidateNumberArrayKey(reply, "values");
				break;
			case FUNCTION_READ_FIFO_QUEUE:
				ValidateBoolKey(reply, "success");
				if (reply.value("success").toBool()) {
					ValidateNumberKey(reply, "byteCount");
					ValidateNumberKey(reply, "fifoCount");
					ValidateNumberArrayKey(reply, "registers");
				}
				break;
			default:
				CUTEHMI_CRITICAL("Unsupported function code '" << function << "'.");
		}
	} catch (const Exception & e) {
		CUTEHMI_CRITICAL("Reply to request '" << id << "' is illformed. " << e.what());
		return false;
	}
	return true;
}

}
}

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
