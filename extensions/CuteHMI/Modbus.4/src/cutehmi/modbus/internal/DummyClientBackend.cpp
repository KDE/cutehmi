#include "internal/DummyClientBackend.hpp"

#include <QThread>
#include <QJsonArray>
#include <QModbusDevice>

namespace cutehmi {
namespace modbus {
namespace internal {

DummyClientBackend::DummyClientBackend(DummyClientConfig * config, QObject * parent):
	AbstractClientBackend(parent),
	m(new Members{config, AbstractDevice::CLOSED, {}, {}, {}, {}})
{
}

DummyClientBackend::~DummyClientBackend()
{
	m->coils.free();
	m->discreteInputs.free();
	m->holdingRegisters.free();
	m->inputRegisters.free();
}

void DummyClientBackend::ensureClosed()
{
	if (m->state != AbstractDevice::CLOSED && m->state != AbstractDevice::CLOSING)
		disconnect();
}

bool DummyClientBackend::proceedRequest(QUuid requestId)
{
	// Normally client would forward the request to Modbus server and emit reply with received data. Dummy client has no remote side
	// to ask, but it emulates the latency here.
	QThread::msleep(static_cast<unsigned long>(qMin(m->config->latency(), m->config->timeout())));	// Fake processing.

	// If fake processing takes longer than timeout return error.
	if (m->config->latency() > m->config->timeout()) {
		QJsonObject reply;

		reply.insert("success", false);
		reply.insert("error", "Timed out.");

		emit replied(requestId, reply);

		return false;
	}

	if (m->state != AbstractDevice::OPENED) {
		QJsonObject reply;

		reply.insert("success", false);
		reply.insert("error", "Client not connected.");

		emit replied(requestId, reply);

		return false;
	}

	return true;
}

void DummyClientBackend::readCoils(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QJsonObject reply;

	QJsonArray values;
	for (quint16 address = startAddress; address <= endAddress; address++)
		values.append(m->coils.value(address)->value());
	reply.insert("values", values);
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::writeCoil(QUuid requestId, quint16 address, bool value)
{
	QJsonObject reply;

	m->coils.value(address)->setValue(value);
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::writeMultipleCoils(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QJsonObject reply;

	quint16 endAddress = startAddress + static_cast<quint16>(values.size()) - 1;	// Size of @a values vector is limited by @ref cutehmi-modbus-AbstractDevice-query_limits.
	for (quint16 address = startAddress; address <= endAddress; address++)
		m->coils.value(address)->setValue(values.at(address));

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::readDiscreteInputs(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QJsonObject reply;

	QJsonArray values;
	for (quint16 address = startAddress; address <= endAddress; address++)
		values.append(m->discreteInputs.value(address)->value());
	reply.insert("values", values);
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::readHoldingRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QJsonObject reply;

	QJsonArray values;
	for (quint16 address = startAddress; address <= endAddress; address++)
		values.append(static_cast<double>(m->holdingRegisters.value(address)->value()));
	reply.insert("values", values);
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::writeHoldingRegister(QUuid requestId, quint16 address, quint16 value)
{
	QJsonObject reply;

	m->holdingRegisters.value(address)->setValue(value);
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::writeMultipleHoldingRegisters(QUuid requestId, quint16 startAddress, const QVector<quint16> & values)
{
	QJsonObject reply;

	quint16 endAddress = startAddress + static_cast<quint16>(values.size()) - 1;	// Size of @a values vector is limited by @ref cutehmi-modbus-AbstractDevice-query_limits.
	for (quint16 address = startAddress; address <= endAddress; address++)
		m->holdingRegisters.value(address)->setValue(values.at(address));

	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::readInputRegisters(QUuid requestId, quint16 startAddress, quint16 endAddress)
{
	QJsonObject reply;

	QJsonArray values;
	for (quint16 address = startAddress; address <= endAddress; address++)
		values.append(static_cast<double>(m->inputRegisters.value(address)->value()));
	reply.insert("values", values);
	reply.insert("success", true);

	emit replied(requestId, reply);
}

void DummyClientBackend::open()
{
	setState(AbstractClient::OPENING);
	QThread::msleep(static_cast<unsigned long>(m->config->openLatency()));
	setState(AbstractClient::OPENED);
	emit opened();
	CUTEHMI_DEBUG("Imaginary connection established.");
}

void DummyClientBackend::close()
{
	setState(AbstractClient::CLOSING);
	QThread::msleep(static_cast<unsigned long>(m->config->closeLatency()));

	setState(AbstractClient::CLOSED);
	emit closed();
	CUTEHMI_DEBUG("Imaginary connection closed.");
}

void DummyClientBackend::setState(AbstractClient::State state)
{
	if (m->state != state) {
		m->state = state;
		emit stateChanged(state);
	}
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
