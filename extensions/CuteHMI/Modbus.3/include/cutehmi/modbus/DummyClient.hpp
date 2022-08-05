#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_DUMMYCLIENT_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_DUMMYCLIENT_HPP

#include "internal/common.hpp"
#include "internal/DummyClientConfig.hpp"
#include "internal/DummyClientBackend.hpp"
#include "internal/PollingIterator.hpp"
#include "AbstractClient.hpp"

#include <QThread>
#include <QQmlEngine>

#include <vector>

namespace cutehmi {
namespace modbus {

/**
 * Dummy client. Dummy client provides implementation of fake Modbus master (client) that connects to imaginary Modbus slave
 * (server). Contrary to real client it can be forced to write to memory regions specified by Modbus protocol as read-only (discrete
 * inputs and input registers). This class is useful when prototyping and testing behavior of client application as it can also
 * emulate latency and it does not require running Modbus slave (server) to work with.
 */
class CUTEHMI_MODBUS_API DummyClient:
	public AbstractClient
{
		Q_OBJECT
		QML_NAMED_ELEMENT(DummyClient)

	public:
		static constexpr int INITIAL_OPEN_LATENCY = internal::DummyClientConfig::INITIAL_OPEN_LATENCY;
		static constexpr int INITIAL_CLOSE_LATENCY = internal::DummyClientConfig::INITIAL_CLOSE_LATENCY;
		static constexpr int INITIAL_LATENCY = internal::DummyClientConfig::INITIAL_LATENCY;

		Q_PROPERTY(int connectLatency READ connectLatency WRITE setConnectLatency NOTIFY connectLatencyChanged)
		Q_PROPERTY(int disconnectLatency READ disconnectLatency WRITE setDisconnectLatency NOTIFY disconnectLatencyChanged)
		Q_PROPERTY(int latency READ latency WRITE setLatency NOTIFY latencyChanged)

		DummyClient(QObject * parent = nullptr);

		~DummyClient() override;

		int connectLatency() const;

		void setConnectLatency(int connectLatency);

		int disconnectLatency() const;

		void setDisconnectLatency(int disconnectLatency);

		int latency() const;

		void setLatency(int latency);

	public slots:
		void open() override;

		void close() override;

	signals:
		void connectLatencyChanged();

		void disconnectLatencyChanged();

		void latencyChanged();

	private:
		struct Members {
			internal::DummyClientConfig config;
			internal::DummyClientBackend backend;
			QThread thread;

			Members():
				backend(& config)
			{
			}
		};

		MPtr<Members> m;
};

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
