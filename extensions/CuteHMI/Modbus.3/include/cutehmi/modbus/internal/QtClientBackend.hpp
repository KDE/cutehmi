#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTCLIENTBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTCLIENTBACKEND_HPP

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

	public slots:
		void ensureClosed();

	signals:
		void opened();

		void closed();

	protected:
		explicit QtClientBackend(std::unique_ptr<QModbusClient> qClient, QObject * parent = nullptr);

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

#endif

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
