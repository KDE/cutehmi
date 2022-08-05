#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_TCPSERVER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_TCPSERVER_HPP

#include "AbstractServer.hpp"
#include "internal/RegisterTraits.hpp"
#include "internal/QtTCPServerBackend.hpp"

#include <cutehmi/macros.hpp>

#include <QThread>
#include <QStateMachine>
#include <QModbusTcpServer>
#include <QQmlEngine>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API TCPServer:
	public AbstractServer
{
		Q_OBJECT
		QML_NAMED_ELEMENT(TCPServer)

	public:
		static constexpr int MIN_SLAVE_ADDRESS = internal::TCPServerConfig::MIN_SLAVE_ADDRESS;
		static constexpr int MAX_SLAVE_ADDRESS = internal::TCPServerConfig::MAX_SLAVE_ADDRESS;
		static const char * INITIAL_HOST;
		static constexpr int INITIAL_PORT = internal::TCPServerConfig::INITIAL_PORT;
		static constexpr int INITIAL_SLAVE_ADDRESS = internal::TCPServerConfig::INITIAL_SLAVE_ADDRESS;
		static constexpr int INITIAL_COILS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_COILS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_COILS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_COILS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX;
		static constexpr int INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN = internal::TCPServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN;
		static constexpr int INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX = internal::TCPServerConfig::INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX;

		Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
		Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
		Q_PROPERTY(int slaveAddress READ slaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)

		TCPServer(QObject * parent = nullptr);

		~TCPServer() override;

		QString host() const;

		void setHost(const QString & host);

		int port() const;

		void setPort(int port);

		int slaveAddress() const;

		void setSlaveAddress(int slaveAddress);

		void setBusy(bool busy) override;

	public slots:
		void open() override;

		void close() override;

	signals:
		void hostChanged();

		void portChanged();

		void slaveAddressChanged();

	private:
		struct Members
		{
			internal::TCPServerConfig config;
			internal::QtTCPServerBackend backend;
			QThread thread;

			Members(internal::QtTCPServer::CoilDataContainer * coilData,
					internal::QtTCPServer::DiscreteInputDataContainer * discreteInputData,
					internal::QtTCPServer::HoldingRegisterDataContainer * holdingRegisterData,
					internal::QtTCPServer::InputRegisterDataContainer * inputRegisterData):
				backend(& config, coilData, discreteInputData, holdingRegisterData, inputRegisterData)
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
