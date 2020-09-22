#include <cutehmi/modbus/internal/RTUServerConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

constexpr int RTUServerConfig::MIN_SLAVE_ADDRESS;
constexpr int RTUServerConfig::MAX_SLAVE_ADDRESS;
const char * RTUServerConfig::INITIAL_PORT = "COM1";
constexpr QSerialPort::Parity RTUServerConfig::INITIAL_PARITY;
constexpr QSerialPort::BaudRate RTUServerConfig::INITIAL_BAUD_RATE;
constexpr QSerialPort::DataBits RTUServerConfig::INITIAL_DATA_BITS;
constexpr QSerialPort::StopBits RTUServerConfig::INITIAL_STOP_BITS;
constexpr int RTUServerConfig::INITIAL_SLAVE_ADDRESS;
constexpr int RTUServerConfig::INITIAL_COILS_ADDRESS_RANGE_MIN;
constexpr int RTUServerConfig::INITIAL_COILS_ADDRESS_RANGE_MAX;
constexpr int RTUServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN;
constexpr int RTUServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX;
constexpr int RTUServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN;
constexpr int RTUServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX;
constexpr int RTUServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN;
constexpr int RTUServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX;

RTUServerConfig::RTUServerConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString RTUServerConfig::port() const
{
	QReadLocker locker(& m->lock);

	return m->port;
}

void RTUServerConfig::setPort(const QString & port)
{
	QWriteLocker locker(& m->lock);

	m->port = port;

	emit configChanged();
}

QSerialPort::Parity RTUServerConfig::parity() const
{
	QReadLocker locker(& m->lock);

	return m->parity;
}

void RTUServerConfig::setParity(QSerialPort::Parity parity)
{
	QWriteLocker locker(& m->lock);

	m->parity = parity;

	emit configChanged();
}

QSerialPort::BaudRate RTUServerConfig::baudRate() const
{
	QReadLocker locker(& m->lock);

	return m->baudRate;
}

void RTUServerConfig::setBaudRate(QSerialPort::BaudRate baudRate)
{
	QWriteLocker locker(& m->lock);

	m->baudRate = baudRate;

	emit configChanged();
}

QSerialPort::DataBits RTUServerConfig::dataBits() const
{
	QReadLocker locker(& m->lock);

	return m->dataBits;
}

void RTUServerConfig::setDataBits(QSerialPort::DataBits dataBits)
{
	QWriteLocker locker(& m->lock);

	m->dataBits = dataBits;

	emit configChanged();
}

QSerialPort::StopBits RTUServerConfig::stopBits() const
{
	QReadLocker locker(& m->lock);

	return m->stopBits;
}

void RTUServerConfig::setStopBits(QSerialPort::StopBits stopBits)
{
	QWriteLocker locker(& m->lock);

	m->stopBits = stopBits;

	emit configChanged();
}

int cutehmi::modbus::internal::RTUServerConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);
	return m->slaveAddress;
}

void RTUServerConfig::setSlaveAddress(int address)
{
	QWriteLocker locker(& m->lock);
	m->slaveAddress = address;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::coilsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->coilsAddressRange;
}

void RTUServerConfig::setCoilsAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->coilsAddressRange = addressRange;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::inputRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->inputRegistersAddressRange;
}

void RTUServerConfig::setInputRegistersAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->inputRegistersAddressRange = addressRange;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::discreteInputsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->discreteInputsAddressRange;
}

void RTUServerConfig::setDiscreteInputsAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->discreteInputsAddressRange = addressRange;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::holdingRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->holdingRegistersAddressRange;
}

void RTUServerConfig::setHoldingRegistersAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->holdingRegistersAddressRange = addressRange;
	emit configChanged();
}

}
}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
