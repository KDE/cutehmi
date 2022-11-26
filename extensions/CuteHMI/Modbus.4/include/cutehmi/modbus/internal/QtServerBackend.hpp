#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTSERVERBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTSERVERBACKEND_HPP

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
