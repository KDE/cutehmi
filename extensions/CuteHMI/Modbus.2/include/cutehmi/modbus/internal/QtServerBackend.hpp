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
		explicit QtServerBackend(std::unique_ptr<QModbusServer> qServer, QObject * parent = nullptr);

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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
