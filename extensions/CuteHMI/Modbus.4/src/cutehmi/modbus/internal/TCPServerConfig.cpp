#include "internal/TCPServerConfig.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

constexpr int TCPServerConfig::MIN_SLAVE_ADDRESS;
constexpr int TCPServerConfig::MAX_SLAVE_ADDRESS;
const char * TCPServerConfig::INITIAL_HOST = "localhost";
constexpr int TCPServerConfig::INITIAL_PORT;
constexpr int TCPServerConfig::INITIAL_SLAVE_ADDRESS;
constexpr quint16 TCPServerConfig::INITIAL_COILS_ADDRESS_RANGE_MIN;
constexpr quint16 TCPServerConfig::INITIAL_COILS_ADDRESS_RANGE_MAX;
constexpr quint16 TCPServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN;
constexpr quint16 TCPServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX;
constexpr quint16 TCPServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN;
constexpr quint16 TCPServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX;
constexpr quint16 TCPServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN;
constexpr quint16 TCPServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX;

TCPServerConfig::TCPServerConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString cutehmi::modbus::internal::TCPServerConfig::host() const
{
	QReadLocker locker(& m->lock);
	return m->host;
}

void TCPServerConfig::setHost(const QString & host)
{
	QWriteLocker locker(& m->lock);
	m->host = host;
	emit configChanged();
}

int cutehmi::modbus::internal::TCPServerConfig::port() const
{
	QReadLocker locker(& m->lock);
	return m->port;
}

void cutehmi::modbus::internal::TCPServerConfig::setPort(int port)
{
	QWriteLocker locker(& m->lock);
	m->port = port;
	emit configChanged();
}

int cutehmi::modbus::internal::TCPServerConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);
	return m->slaveAddress;
}

void TCPServerConfig::setSlaveAddress(int address)
{
	QWriteLocker locker(& m->lock);
	m->slaveAddress = address;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::coilsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->coilsAddressRange;
}

void TCPServerConfig::setCoilsAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->coilsAddressRange = addressRange;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::inputRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->inputRegistersAddressRange;
}

void TCPServerConfig::setInputRegistersAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->inputRegistersAddressRange = addressRange;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::discreteInputsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->discreteInputsAddressRange;
}

void TCPServerConfig::setDiscreteInputsAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->discreteInputsAddressRange = addressRange;
	emit configChanged();
}

TCPServerConfig::AddressRange TCPServerConfig::holdingRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->holdingRegistersAddressRange;
}

void TCPServerConfig::setHoldingRegistersAddressRange(TCPServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->holdingRegistersAddressRange = addressRange;
	emit configChanged();
}

}
}
}

//(c)C: Copyright © 2022-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
