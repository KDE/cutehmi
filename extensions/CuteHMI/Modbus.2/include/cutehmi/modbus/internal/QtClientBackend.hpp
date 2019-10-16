#ifndef INCLUDECUTEHMIMODBUSINTERNALQTCLIENTBACKEND_HPP
#define INCLUDECUTEHMIMODBUSINTERNALQTCLIENTBACKEND_HPP

#include "common.hpp"
#include "Config.hpp"
#include "AbstractClientBackend.hpp"

#include <memory>

#include <QModbusClient>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE QtClientBackend:
	public AbstractClientBackend
{
		Q_OBJECT

	public:
		QtClientBackend(std::unique_ptr<QModbusClient> qClient, QObject * parent = nullptr);

	public slots:
		void ensureClosed();

	signals:
		void opened();

		void closed();

	protected:
		virtual int slaveAddress() const = 0;

		virtual void configureConnection() = 0;

		QModbusClient * qClient() const;

		bool proceedRequest(QUuid requestId) override;

		void readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeCoil(QUuid requestId, quint16 address, bool value) override;

		void writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

		void readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeHoldingRegister(QUuid requestId, quint16 address, quint16 value) override;

		void writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

		void readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void readExceptionStatus(QUuid requestId) override;

		void diagnostics(QUuid requestId, AbstractDevice::DiagnosticsSubfunction subfunction, quint16 data) override;

		void fetchCommEventCounter(QUuid requestId) override;

		void fetchCommEventLog(QUuid requestId) override;

		void reportSlaveId(QUuid requestId) override;

		void readFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests) override;

		void writeFileRecord(QUuid requestId, quint8 byteCount, QJsonArray subrequests) override;

		void maskWriteHoldingRegister(QUuid requestId, quint16 address, quint16 andMask, quint16 orMask) override;

		void readWriteMultipleHoldingRegisters(QUuid requestId, quint16 readStartAddress, quint16 readEndAddress, quint16 writeAddress, const QVector<quint16> & values) override;

		void readFIFOQueue(QUuid requestId, quint16 address) override;

	protected slots:
		void open() override;

		void close() override;

	private slots:
		void onStateChanged(QModbusDevice::State state);

		void onErrorOccurred(QModbusDevice::Error error);

		void printError(cutehmi::InplaceError error) const;

	private:
		void writeDataUnit(QUuid requestId, const QModbusDataUnit & unit);

		void readDataUnitInt(QUuid requestId, const QModbusDataUnit & unit);

		void readDataUnitBool(QUuid requestId, const QModbusDataUnit & unit);

		void prepareErrorReply(const QModbusReply & modbusReply, QJsonObject & reply);

		/**
		 * Write byte (octet) into destination byte array.
		 * @param byte byte to be stored.
		 * @param destination destination array. Array pointer will be modified to point to a location past the stored byte.
		 */
		void pushByte(uchar byte, uchar *& destination);

		/**
		 * Write word (two octets) into destination byte array. Word is stored in destination array in big-endian order.
		 * @param word word to be stored.
		 * @param destination destination array. Array pointer will be modified to point to a location past the stored word.
		 */
		void pushWord(uint word, uchar *& destination);

		/**
		 * Read byte (octet) from a byte array.
		 * @param source array to be read. Array pointer will be modified to point to a location past the read byte.
		 * @return byte read from @a source.
		 */
		uchar pullByte(const uchar *& source);

		/**
		 * Read word (two octets) from a byte array. Array is expected to be in big-endian order.
		 * @param source array to be read. Array pointer will be modified to point to a location past the read word.
		 * @return word read from @a source.
		 */
		uint pullWord(const uchar *& source);

		struct Members
		{
			QModbusClient * qClient;
		};

		MPtr<Members> m;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALQTCLIENTBACKEND_HPP
