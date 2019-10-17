#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTSERVERBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTSERVERBACKEND_HPP

#include "common.hpp"
#include "Config.hpp"
#include "AbstractServerBackend.hpp"

#include <memory>

#include <QModbusServer>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE QtServerBackend:
	public AbstractServerBackend
{
		Q_OBJECT

	public:
		QtServerBackend(std::unique_ptr<QModbusServer> qServer, QObject * parent = nullptr);

	public slots:
		void ensureClosed();

	signals:
		void opened();

		void closed();

		void coilsWritten(quint16 address, quint16 amount);

		void discreteInputsWritten(quint16 address, quint16 amount);

		void holdingRegistersWritten(quint16 address, quint16 amount);

		void inputRegistersWritten(quint16 address, quint16 amount);

	protected:
		virtual int slaveId() const = 0;

		virtual void configureConnection() = 0;

		QModbusServer * qServer() const;

		bool proceedRequest(QUuid requestId) override;

		void readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeCoil(QUuid requestId, quint16 address, bool value) override;

		void writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

		void readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeDiscreteInput(QUuid requestId, quint16 address, bool value) override;

		void writeMultipleDiscreteInputs(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

		void readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeHoldingRegister(QUuid requestId, quint16 address, quint16 value) override;

		void writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

		void readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress) override;

		void writeInputRegister(QUuid requestId, quint16 address, quint16 value) override;

		void writeMultipleInputRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values) override;

	protected slots:
		void open() override;

		void close() override;

		void setBusy(bool busy) override;

	private:
		void readDataUnitInt(QUuid requestId, QModbusDataUnit & unit);

		void readDataUnitBool(QUuid requestId, QModbusDataUnit & unit);

	private slots:
		void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);

		void onStateChanged(QModbusDevice::State state);

		void onErrorOccurred(QModbusDevice::Error error);

		void printError(cutehmi::InplaceError error) const;

	private:
		struct Members
		{
			QModbusServer * qServer;
		};

		MPtr<Members> m;

};

}
}
}

#endif
