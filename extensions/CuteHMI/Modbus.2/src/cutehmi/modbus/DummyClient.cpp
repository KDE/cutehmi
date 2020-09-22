#include <cutehmi/modbus/DummyClient.hpp>

#include <cutehmi/modbus/internal/HoldingRegisterPolling.hpp>

#include <QJsonArray>

namespace cutehmi {
namespace modbus {

constexpr int DummyClient::INITIAL_OPEN_LATENCY;
constexpr int DummyClient::INITIAL_CLOSE_LATENCY;
constexpr int DummyClient::INITIAL_LATENCY;

DummyClient::DummyClient(QObject * parent):
	AbstractClient(parent),
	m(new Members)
{
	m->backend.moveToThread(& m->thread);

	connect(& m->thread, & QThread::finished, & m->backend, & internal::DummyClientBackend::ensureClosed);

	connect(this, & DummyClient::requestReceived, & m->backend, & internal::DummyClientBackend::processRequest);

	connect(& m->backend, & internal::DummyClientBackend::replied, this, & DummyClient::handleReply);

	connect(& m->backend, & internal::DummyClientBackend::stateChanged, this, & DummyClient::setState);

	connect(& m->backend, & internal::DummyClientBackend::closed, this, & DummyClient::stopped);

	connect(& m->backend, & internal::DummyClientBackend::opened, this, & DummyClient::started);

	connect(& m->backend, & internal::DummyClientBackend::errored, this, & DummyClient::broke);
	connect(& m->backend, & internal::DummyClientBackend::closed, this, & DummyClient::broke);

	m->thread.start();
}

DummyClient::~DummyClient()
{
	m->thread.quit();
	m->thread.wait();
}

int DummyClient::connectLatency() const
{
	return m->config.openLatency();
}

void DummyClient::setConnectLatency(int connectLatency)
{
	if (m->config.openLatency() != connectLatency) {
		m->config.setOpenLatency(connectLatency);
		emit connectLatencyChanged();
	}
}

int DummyClient::disconnectLatency() const
{
	return m->config.closeLatency();
}

void DummyClient::setDisconnectLatency(int disconnectLatency)
{
	if (m->config.closeLatency() != disconnectLatency) {
		m->config.setCloseLatency(disconnectLatency);
		emit disconnectLatencyChanged();
	}
}

int DummyClient::latency() const
{
	return m->config.latency();
}

void DummyClient::setLatency(int latency)
{
	if (m->config.latency() != latency) {
		m->config.setLatency(latency);
		emit latencyChanged();
	}
}

void DummyClient::open()
{
	emit m->backend.openRequested();
}

void DummyClient::close()
{
	emit m->backend.closeRequested();
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
