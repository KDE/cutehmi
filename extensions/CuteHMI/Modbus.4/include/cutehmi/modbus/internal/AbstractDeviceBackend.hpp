#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ABSTRACTDEVICEBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ABSTRACTDEVICEBACKEND_HPP

#include "common.hpp"
#include "RegisterTraits.hpp"
#include "../AbstractClient.hpp"

#include <cutehmi/InplaceError.hpp>

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

	public slots:
		virtual void processRequest(QJsonObject request);

	signals:
		void replied(QUuid requestId, QJsonObject reply);

		void errored(cutehmi::InplaceError error);

		void stateChanged(cutehmi::modbus::AbstractDevice::State state);

		void openRequested();

		void closeRequested();

	protected:
		explicit AbstractDeviceBackend(QObject * parent = nullptr);

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

#endif

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
