#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_TCPCLIENT_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_TCPCLIENT_HPP

#include "AbstractClient.hpp"
#include "internal/QtTCPClientBackend.hpp"

#include <QThread>

namespace cutehmi {
namespace modbus {

/**
 * Modbus TCP client.
 */
class CUTEHMI_MODBUS_API TCPClient:
	public AbstractClient
{
		Q_OBJECT

	public:
		static constexpr int MIN_SLAVE_ADDRESS = internal::TCPClientConfig::MIN_SLAVE_ADDRESS;
		static constexpr int MAX_SLAVE_ADDRESS = internal::TCPClientConfig::MAX_SLAVE_ADDRESS;
		static const char * INITIAL_HOST;
		static constexpr int INITIAL_PORT = internal::TCPClientConfig::INITIAL_PORT;
		static constexpr int INITIAL_SLAVE_ADDRESS = internal::TCPClientConfig::INITIAL_SLAVE_ADDRESS;

		Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
		Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
		Q_PROPERTY(int slaveAddress READ slaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)

		TCPClient(QObject * parent = nullptr);

		~TCPClient() override;

		QString host() const;

		void setHost(const QString & host);

		int port() const;

		void setPort(int port);

		int slaveAddress() const;

		void setSlaveAddress(int slaveAddress);

	public slots:
		void open() override;

		void close() override;

	signals:
		void hostChanged();

		void portChanged();

		void slaveAddressChanged();

	private:
		struct Members {
			internal::TCPClientConfig config;
			internal::QtTCPClientBackend backend;
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
