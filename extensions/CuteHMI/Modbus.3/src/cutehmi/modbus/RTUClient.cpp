#include <cutehmi/modbus/RTUClient.hpp>

namespace cutehmi {
namespace modbus {

constexpr int RTUClient::MIN_SLAVE_ADDRESS;
constexpr int RTUClient::MAX_SLAVE_ADDRESS;
const char * RTUClient::INITIAL_PORT = internal::RTUClientConfig::INITIAL_PORT;
constexpr QSerialPort::Parity RTUClient::INITIAL_PARITY;
constexpr QSerialPort::BaudRate RTUClient::INITIAL_BAUD_RATE;
constexpr QSerialPort::DataBits RTUClient::INITIAL_DATA_BITS;
constexpr QSerialPort::StopBits RTUClient::INITIAL_STOP_BITS;
constexpr int RTUClient::INITIAL_SLAVE_ADDRESS;

RTUClient::RTUClient(QObject * parent):
	AbstractClient(parent),
	m(new Members)
{
	m->backend.moveToThread(& m->thread);

	connect(& m->thread, & QThread::finished, & m->backend, & internal::QtClientBackend::ensureClosed);

	connect(this, & RTUClient::requestAccepted, & m->backend, & internal::QtClientBackend::processRequest);

	connect(& m->backend, & internal::QtClientBackend::replied, this, & RTUClient::handleReply);

	connect(& m->backend, & internal::QtClientBackend::stateChanged, this, & RTUClient::setState);

	connect(& m->backend, & internal::QtClientBackend::closed, this, & RTUClient::stopped);

	connect(& m->backend, & internal::QtClientBackend::opened, this, & RTUClient::started);

	connect(& m->backend, & internal::QtClientBackend::errored, this, & AbstractDevice::errored);
	connect(& m->backend, & internal::QtClientBackend::closed, this, & RTUClient::broke);

	m->thread.start();
}

RTUClient::~RTUClient()
{
	m->thread.quit();
	m->thread.wait();
}

QString RTUClient::port() const
{
	return m->config.port();
}

void RTUClient::setPort(const QString & port)
{
	if (m->config.port() != port) {
		m->config.setPort(port);
		emit portChanged();
	}
}

QSerialPort::Parity RTUClient::parity() const
{
	return m->config.parity();
}

void RTUClient::setParity(QSerialPort::Parity parity)
{
	if (m->config.parity() != parity) {
		m->config.setParity(parity);
		emit parityChanged();
	}
}

QSerialPort::BaudRate RTUClient::baudRate() const
{
	return m->config.baudRate();
}

void RTUClient::setBaudRate(QSerialPort::BaudRate baudRate)
{
	if (m->config.baudRate() != baudRate) {
		m->config.setBaudRate(baudRate);
		emit baudRateChanged();
	}
}

QSerialPort::DataBits RTUClient::dataBits() const
{
	return m->config.dataBits();
}

void RTUClient::setDataBits(QSerialPort::DataBits dataBits)
{
	if (m->config.dataBits() != dataBits) {
		m->config.setDataBits(dataBits);
		emit dataBitsChanged();
	}
}

QSerialPort::StopBits RTUClient::stopBits() const
{
	return m->config.stopBits();
}

void RTUClient::setStopBits(QSerialPort::StopBits stopBits)
{
	if (m->config.stopBits() != stopBits) {
		m->config.setStopBits(stopBits);
		emit stopBitsChanged();
	}
}

int RTUClient::slaveAddress() const
{
	return m->config.slaveAddress();
}

void RTUClient::setSlaveAddress(int slaveAddress)
{
	if (m->config.slaveAddress() != slaveAddress) {
		m->config.setSlaveAddress(slaveAddress);
		emit slaveAddressChanged();
	}
}

void RTUClient::open()
{
	emit m->backend.openRequested();
}

void RTUClient::close()
{
	emit m->backend.closeRequested();
}

}
}

//(c)C: Copyright © 2021-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
