#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_DUMMYCLIENT_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_DUMMYCLIENT_HPP

#include "internal/common.hpp"
#include "internal/DummyClientConfig.hpp"
#include "internal/DummyClientBackend.hpp"
#include "internal/PollingIterator.hpp"
#include "AbstractClient.hpp"

#include <cutehmi/services/PollingTimer.hpp>

#include <QThread>

#include <vector>

namespace cutehmi {
namespace modbus {

/**
 * Dummy client. Dummy client provides implementation of fake Modbus master (client) that connects to imaginary Modbus slave
 * (server). Contrary to real client it can be forced to write to memory regions specified by Modbus protocol as read-only (discrete
 * inputs and input registers). This class is useful when prototyping and testing behavior of client application as it can also
 * emulate latency and it does not require running Modbus slave (server) to work with.
 *
 * @todo random failures (unsuccesful requests, broken connections etc).
 */
class CUTEHMI_MODBUS_API DummyClient:
	public AbstractClient
{
		Q_OBJECT

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

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
