#include <cutehmi/modbus/internal/QtClientBackend.hpp>

#include <cutehmi/modbus/internal/functions.hpp>

#include <QThread>
#include <QJsonArray>

namespace cutehmi {
namespace modbus {
namespace internal {

QtClientBackend::QtClientBackend(std::unique_ptr<QModbusClient> qClient, QObject * parent):
	AbstractClientBackend(parent),
	m(new Members{qClient.get()})
{
	qClient.release()->setParent(this);
//	connect(& config, & Config::configChanged, this, & QtClientBackend::configureConnection);
	connect(m->qClient, & QModbusClient::stateChanged, this, & QtClientBackend::onStateChanged);
	connect(m->qClient, & QModbusClient::errorOccurred, this, & QtClientBackend::onErrorOccurred);
	connect(this, & QtClientBackend::errored, this, & QtClientBackend::printError);
}

void QtClientBackend::ensureClosed()
{
	if (m->qClient->state() != QModbusDevice::UnconnectedState && m->qClient->state() != QModbusDevice::ClosingState)
		disconnect();
}

QModbusClient * QtClientBackend::qClient() const
{
	return m->qClient;
}

bool QtClientBackend::proceedRequest(QUuid requestId)
{
	if (m->qClient->state() != QModbusDevice::ConnectedState) {
		QJsonObject reply;

		reply.insert("success", false);
		reply.insert("error", "Client not connected.");

		emit replied(requestId, reply);

		return false;
	}
	return true;
}

void QtClientBackend::readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit unit(QModbusDataUnit::Coils, startAddress, endAddress - startAddress + 1);
	readDataUnitBool(requestId, unit);
}

void QtClientBackend::writeCoil(QUuid requestId, quint16 address, bool value)
{
	QModbusDataUnit unit(QModbusDataUnit::Coils, address, QVector<quint16> {value});
	writeDataUnit(requestId, unit);
}

void QtClientBackend::writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QModbusDataUnit unit(QModbusDataUnit::Coils, startAddress, values);
	writeDataUnit(requestId, unit);
}

void QtClientBackend::readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit unit(QModbusDataUnit::DiscreteInputs, startAddress, endAddress - startAddress + 1);
	readDataUnitBool(requestId, unit);
}

void QtClientBackend::readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, startAddress, endAddress - startAddress + 1);
	readDataUnitInt(requestId, unit);
}

void QtClientBackend::writeHoldingRegister(QUuid requestId, quint16 address, quint16 value)
{
	QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, address, QVector<quint16> {value});
	writeDataUnit(requestId, unit);
}

void QtClientBackend::writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, startAddress, values);
	writeDataUnit(requestId, unit);
}

void QtClientBackend::readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QModbusDataUnit unit(QModbusDataUnit::InputRegisters, startAddress, endAddress - startAddress + 1);
	readDataUnitInt(requestId, unit);
}

void QtClientBackend::readExceptionStatus(QUuid requestId)
{
	QModbusRequest request(QModbusPdu::ReadExceptionStatus);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 1) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					reply.insert("exceptionStatus", static_cast<double>(pullByte(data)));
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::diagnostics(QUuid requestId, AbstractDevice::DiagnosticsSubfunction subfunction, quint16 data)
{
	QByteArray requestArray(4, 0x0);
	uchar * requestData = reinterpret_cast<uchar *>(requestArray.data());
	pushWord(subfunction, requestData);
	pushWord(data, requestData);

	QModbusRequest request(QModbusPdu::Diagnostics, requestArray);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 4) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					reply.insert("subfunction", static_cast<double>(pullWord(data)));
					reply.insert("data", static_cast<double>(pullWord(data)));
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::fetchCommEventCounter(QUuid requestId)
{
	QModbusRequest request(QModbusPdu::GetCommEventCounter);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 4) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					reply.insert("status", static_cast<double>(pullWord(data)));
					reply.insert("eventCount", static_cast<double>(pullWord(data)));
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::fetchCommEventLog(QUuid requestId)
{
	QModbusRequest request(QModbusPdu::GetCommEventLog);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 7) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					uchar byteCount = pullByte(data);
					reply.insert("byteCount", static_cast<double>(byteCount));
					reply.insert("status", static_cast<double>(pullWord(data)));
					reply.insert("eventCount", static_cast<double>(pullWord(data)));
					reply.insert("messageCount", static_cast<double>(pullWord(data)));
					QJsonArray events;
					for (uchar byte = 7; byte <= byteCount; byte++)
						events.append(static_cast<double>(pullByte(data)));
					reply.insert("events", events);
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::reportSlaveId(QUuid requestId)
{
	QModbusRequest request(QModbusPdu::ReportServerId);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 3) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					uchar byteCount = pullByte(data);
					reply.insert("byteCount", static_cast<double>(byteCount));
					reply.insert("slaveId", static_cast<double>(pullByte(data)));
					reply.insert("runIndicatorStatus", static_cast<double>(pullByte(data)));
					QJsonArray additionalData;
					for (uchar byte = 3; byte <= byteCount; byte++)
						additionalData.append(static_cast<double>(pullByte(data)));
					reply.insert("additionalData", additionalData);
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::readFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests)
{
	QByteArray requestArray(byteCount + 1, 0x0);	// +1 byte for byteCount itself.
	uchar * requestData = reinterpret_cast<uchar *>(requestArray.data());
	pushByte(byteCount, requestData);
	for (int i = 0; i < subrequests.count(); i++) {
		QJsonObject subrequest = subrequests.at(i).toObject();
		uchar referenceType = static_cast<uchar>(subrequest.value("referenceType").toDouble());
		uint file = static_cast<uint>(subrequest.value("file").toDouble());
		uint address = static_cast<uint>(subrequest.value("address").toDouble());
		uint amount = static_cast<uint>(subrequest.value("amount").toDouble());
		pushByte(referenceType, requestData);
		pushWord(file, requestData);
		pushWord(address, requestData);
		pushWord(amount, requestData);
	}

	QModbusRequest request(QModbusPdu::ReadFileRecord, requestArray);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 1) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					uchar byteCount = pullByte(data);
					reply.insert("byteCount", static_cast<double>(byteCount));
					QJsonArray subresponeses;
					uchar byte = 1;
					while (byte <= byteCount) {
						QJsonObject subresponse;

						uchar subByteCount = pullByte(data);
						subresponse.insert("byteCount", static_cast<double>(subByteCount));

						subresponse.insert("referenceType", static_cast<double>(pullByte(data)));

						QJsonArray values;
						for (uchar subByte = 2; subByte <= subByteCount; subByte += 2)
							values.append(static_cast<double>(pullWord(data)));
						subresponse.insert("values", values);

						subresponeses.append(subresponse);
						byte += subByteCount + 1;	// +1 for subByteCount itself.
					}
					reply.insert("subresponses", subresponeses);
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::writeFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests)
{
	QByteArray requestArray(byteCount + 1, 0x0);	// +1 byte for byteCount itself.
	uchar * requestData = reinterpret_cast<uchar *>(requestArray.data());
	pushByte(byteCount, requestData);
	for (int i = 0; i < subrequests.count(); i++) {
		QJsonObject subrequest = subrequests.at(i).toObject();
		uchar referenceType = static_cast<uchar>(subrequest.value("referenceType").toDouble());
		uint file = static_cast<uint>(subrequest.value("file").toDouble());
		uint address = static_cast<uint>(subrequest.value("address").toDouble());
		QJsonArray values = subrequest.value("values").toArray();
		uint amount = static_cast<uint>(values.count());
		pushByte(referenceType, requestData);
		pushWord(file, requestData);
		pushWord(address, requestData);
		pushWord(amount, requestData);
		for (auto value = values.begin(); value != values.end(); ++value)
			pushWord(static_cast<quint16>(value->toDouble()), requestData);
	}

	QModbusRequest request(QModbusPdu::WriteFileRecord, requestArray);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 1) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					uchar byteCount = pullByte(data);
					reply.insert("byteCount", static_cast<double>(byteCount));
					QJsonArray subresponeses;
					uchar byte = 1;
					while (byte <= byteCount) {
						QJsonObject subresponse;

						subresponse.insert("referenceType", static_cast<double>(pullByte(data)));

						subresponse.insert("file", static_cast<double>(pullWord(data)));

						subresponse.insert("address", static_cast<double>(pullWord(data)));

						uint amount = pullWord(data);
						subresponse.insert("amount", static_cast<double>(amount));

						QJsonArray values;
						for (uint i = 0; i < amount; i++)
							values.append(static_cast<double>(pullWord(data)));
						subresponse.insert("values", values);

						subresponeses.append(subresponse);
						byte += 7 + values.count() * 2;
					}
					reply.insert("subresponses", subresponeses);
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::maskWriteHoldingRegister(QUuid requestId, quint16 address, quint16 andMask, quint16 orMask)
{
	QByteArray requestArray(6, 0x0);
	uchar * requestData = reinterpret_cast<uchar *>(requestArray.data());
	pushWord(address, requestData);
	pushWord(andMask, requestData);
	pushWord(orMask, requestData);

	QModbusRequest request(QModbusPdu::MaskWriteRegister, requestArray);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 4) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					reply.insert("address", static_cast<double>(pullWord(data)));
					reply.insert("andMask", static_cast<double>(pullWord(data)));
					reply.insert("orMask", static_cast<double>(pullWord(data)));
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::readWriteMultipleHoldingRegisters(QUuid requestId, quint16 readStartAddress, quint16 readEndAddress, quint16 writeAddress, const QVector<quint16> & values)
{
	QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, readStartAddress, readEndAddress - readStartAddress + 1);
	QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, writeAddress, values);

	QModbusReply * modbusReply = m->qClient->sendReadWriteRequest(readUnit, writeUnit, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				auto modbusValues = modbusReply->result().values();
				QJsonArray values;
				for (auto modbusValue = modbusValues.begin(); modbusValue != modbusValues.end(); ++modbusValue)
					values.append(static_cast<double>(*modbusValue));
				reply.insert("values", values);
				reply.insert("success", true);
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::readFIFOQueue(QUuid requestId, quint16 address)
{
	QByteArray requestArray(2, 0x0);
	uchar * requestData = reinterpret_cast<uchar *>(requestArray.data());
	pushWord(address, requestData);

	QModbusRequest request(QModbusPdu::ReadFifoQueue, requestArray);
	QModbusReply * modbusReply = m->qClient->sendRawRequest(request, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				QModbusResponse response = modbusReply->rawResult();
				if (response.data().size() >= 4) {
					QByteArray dataArray = response.data();
					const uchar * data = reinterpret_cast<const uchar *>(dataArray.data());
					reply.insert("byteCount", static_cast<double>(pullWord(data)));
					uint fifoCount = pullWord(data);
					reply.insert("fifoCount", static_cast<double>(fifoCount));
					QJsonArray registers;
					for (uint reg = 0; reg < fifoCount; reg++)
						registers.append(static_cast<double>(pullWord(data)));
					reply.insert("registers", registers);
					reply.insert("success", true);
				} else {
					reply.insert("error", "Device response is incomplete.");
					reply.insert("success", false);
				}
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::open()
{
	if (m->qClient->state() == QModbusDevice::ConnectedState)
		CUTEHMI_DEBUG("Ignoring request - already connected.");
	else if (m->qClient->state() == QModbusDevice::ConnectingState)
		CUTEHMI_DEBUG("Ignoring request - client is already trying to connect to the server.");
	else if (m->qClient->state() == QModbusDevice::UnconnectedState) {
		configureConnection();
		if (!m->qClient->connectDevice())
			emit errored(CUTEHMI_ERROR(tr("Failed to initialize connection.")));
	} else {
		if (m->qClient->state() == QModbusDevice::ClosingState) {
			CUTEHMI_WARNING("Request ignored - client is currently proceeding with disconnect operation, which prevents it from initiating a connection to the server.");
			emit errored(CUTEHMI_ERROR(tr("Client is currently proceeding with disconnect operation.")));
		} else {
			CUTEHMI_CRITICAL("Request ignored - client is in some unrecognized state, which prevents it from connecting to the server.");
			emit errored(CUTEHMI_ERROR(tr("Client is in some unrecognized state, which prevents it from initiating a connection to the server.")));
		}
	}
}

void QtClientBackend::close()
{
	if (m->qClient->state() == QModbusDevice::UnconnectedState)
		CUTEHMI_DEBUG("Ignoring request - already disconnected.");
	else if (m->qClient->state() == QModbusDevice::ClosingState)
		CUTEHMI_DEBUG("Ignoring request - client is already trying to disconnect.");
	else do {
			if (m->qClient->state() == QModbusDevice::ConnectedState) {
				m->qClient->disconnectDevice();
			} else {
				QThread::yieldCurrentThread();
				QCoreApplication::processEvents();
			}
		} while (m->qClient->state() != QModbusDevice::UnconnectedState);
}

void QtClientBackend::onStateChanged(QModbusDevice::State state)
{
	CUTEHMI_DEBUG("Client state changed to: '" << state << "'.");
	switch (m->qClient->state()) {
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

void QtClientBackend::onErrorOccurred(QModbusDevice::Error error)
{
	Q_UNUSED(error)

	emit errored(CUTEHMI_ERROR(m->qClient->errorString()));
}

void QtClientBackend::printError(InplaceError error) const
{
	CUTEHMI_WARNING(error.str());
}

void QtClientBackend::writeDataUnit(QUuid requestId, const QModbusDataUnit & unit)
{
	QModbusReply * modbusReply = m->qClient->sendWriteRequest(unit, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError)
				reply.insert("success", true);
			else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::readDataUnitInt(QUuid requestId, const QModbusDataUnit & unit)
{
	QModbusReply * modbusReply = m->qClient->sendReadRequest(unit, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				auto modbusValues = modbusReply->result().values();
				QJsonArray values;
				for (auto modbusValue = modbusValues.begin(); modbusValue != modbusValues.end(); ++modbusValue)
					values.append(static_cast<double>(*modbusValue));
				reply.insert("values", values);
				reply.insert("success", true);
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::readDataUnitBool(QUuid requestId, const QModbusDataUnit & unit)
{
	QModbusReply * modbusReply = m->qClient->sendReadRequest(unit, slaveAddress());
	if (!modbusReply->isFinished()) {
		connect(modbusReply, & QModbusReply::finished, this, [this, modbusReply, requestId]() {
			QJsonObject reply;
			if (modbusReply->error() == QModbusDevice::NoError) {
				auto modbusValues = modbusReply->result().values();
				QJsonArray values;
				for (auto modbusValue = modbusValues.begin(); modbusValue != modbusValues.end(); ++modbusValue)
					values.append(static_cast<bool>(*modbusValue));
				reply.insert("values", values);
				reply.insert("success", true);
			} else
				prepareErrorReply(*modbusReply, reply);

			emit replied(requestId, reply);

			modbusReply->deleteLater();
		});
	} else {
		// Referring to Qt Serial Bus 'master' example "broadcast replies return immediately".
		emit replied(requestId, QJsonObject());
		modbusReply->deleteLater();
	}
}

void QtClientBackend::prepareErrorReply(const QModbusReply & modbusReply, QJsonObject & reply)
{
	reply.insert("error", modbusReply.errorString());
	reply.insert("errorCode", modbusReply.error());
	if (modbusReply.error() == QModbusDevice::ProtocolError)
		reply.insert("protocolErrorCode", modbusReply.rawResult().exceptionCode());
	reply.insert("success", false);
}

void QtClientBackend::pushByte(uchar byte, uchar *& destination)
{
	*destination = byte;
	destination++;
}

void QtClientBackend::pushWord(uint word, uchar *& destination)
{
	static constexpr uint BYTE_MASK = 0xFF;

	*destination = static_cast<uchar>(word >> 8 & BYTE_MASK);
	destination++;

	*destination = static_cast<uchar>(word & BYTE_MASK);
	destination++;
}

uchar QtClientBackend::pullByte(const uchar *& source)
{
	return *source++;
}

uint QtClientBackend::pullWord(const uchar *& source)
{
	uint result = static_cast<uint>(source[0]) << 8 | static_cast<uint>(source[1]);
	source += 2;
	return result;
}

}
}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
