#ifndef INCLUDECUTEHMIMODBUSINTERNALABSTRACTDEVICEBACKEND_HPP
#define INCLUDECUTEHMIMODBUSINTERNALABSTRACTDEVICEBACKEND_HPP

#include "common.hpp"
#include "RegisterTraits.hpp"

#include <cutehmi/InplaceError.hpp>
#include <cutehmi/modbus/AbstractClient.hpp>

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Abstract device backend. By design backend lives in separate thread, thus communication with backend instances are allowed only
 * through signals & slots mechanism or thread-safe functions.
 */
class CUTEHMI_MODBUS_PRIVATE AbstractDeviceBackend:
	public QObject
{
		Q_OBJECT

	public:
		AbstractDeviceBackend(QObject * parent = nullptr);

	public slots:
		virtual void processRequest(QJsonObject request);

	signals:
		void replied(QUuid requestId, QJsonObject reply);

		void errored(cutehmi::InplaceError error);

		void stateChanged(cutehmi::modbus::AbstractDevice::State state);

		void openRequested();

		void closeRequested();

	protected:
		virtual bool proceedRequest(QUuid requestId) = 0;

		virtual void readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress);

		virtual void writeCoil(QUuid requestId, quint16 address, bool value);

		virtual void writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values);

		virtual void readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress);

		virtual void writeDiscreteInput(QUuid requestId, quint16 address, bool value);

		virtual void writeMultipleDiscreteInputs(QUuid requestId, quint16 startAddress, const QVector<quint16> & values);

		virtual void readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress);

		virtual void writeHoldingRegister(QUuid requestId, quint16 address, quint16 value);

		virtual void writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values);

		virtual void readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress);

		virtual void writeInputRegister(QUuid requestId, quint16 address, quint16 value);

		virtual void writeMultipleInputRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values);

		virtual void readExceptionStatus(QUuid requestId);

		virtual void diagnostics(QUuid requestId, AbstractDevice::DiagnosticsSubfunction subfunction, quint16 data);

		virtual void fetchCommEventCounter(QUuid requestId);

		virtual void fetchCommEventLog(QUuid requestId);

		virtual void reportSlaveId(QUuid requestId);

		virtual void readFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests);

		virtual void writeFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests);

		virtual void maskWriteHoldingRegister(QUuid requestId, quint16 address, quint16 andMask, quint16 orMask);

		virtual void readWriteMultipleHoldingRegisters(QUuid requestId, quint16 readStartAddress, quint16 readEndAddress, quint16 writeAddress, const QVector<quint16> & values);

		virtual void readFIFOQueue(QUuid requestId, quint16 address);

	protected slots:
		virtual void open() = 0;

		virtual void close() = 0;

	private:
		void replyIllegalFunction(QUuid requestId);

		const char * humanFunctionName(AbstractDevice::Function) const;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALABSTRACTCLIENTBACKEND_HPP
