#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_TCPSERVERCONFIG_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_TCPSERVERCONFIG_HPP

#include "Config.hpp"

#include <QObject>
#include <QString>
#include <QReadWriteLock>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE TCPServerConfig:
	public Config
{
		Q_OBJECT

	public:
		typedef std::pair<quint16, quint16> AddressRange;

		static constexpr int MIN_SLAVE_ADDRESS = 1; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static constexpr int MAX_SLAVE_ADDRESS = 247; // Can be 1 to 247 according to http://www.simplymodbus.ca/FAQ.htm
		static const char * INITIAL_HOST;
		static constexpr int INITIAL_PORT = 502;
		static constexpr int INITIAL_SLAVE_ADDRESS = MIN_SLAVE_ADDRESS;
		static constexpr quint16 INITIAL_COILS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_COILS_ADDRESS_RANGE_MAX = 65535;
		static constexpr quint16 INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX = 65535;
		static constexpr quint16 INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX = 65535;
		static constexpr quint16 INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN = 0;
		static constexpr quint16 INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX = 65535;

		explicit TCPServerConfig(QObject * parent = nullptr);

		QString host() const;

		void setHost(const QString & host);

		int port() const;

		void setPort(int port);

		int slaveAddress() const;

		void setSlaveAddress(int address);

		AddressRange coilsAddressRange() const;

		void setCoilsAddressRange(AddressRange addressRange);

		AddressRange inputRegistersAddressRange() const;

		void setInputRegistersAddressRange(AddressRange addressRange);

		AddressRange discreteInputsAddressRange() const;

		void setDiscreteInputsAddressRange(AddressRange addressRange);

		AddressRange holdingRegistersAddressRange() const;

		void setHoldingRegistersAddressRange(AddressRange addressRange);

	private:
		struct Members
		{
			QString host = INITIAL_HOST;
			int	port = INITIAL_PORT;
			int slaveAddress = INITIAL_SLAVE_ADDRESS;
			AddressRange coilsAddressRange = AddressRange(INITIAL_COILS_ADDRESS_RANGE_MIN, INITIAL_COILS_ADDRESS_RANGE_MAX);
			AddressRange discreteInputsAddressRange = AddressRange(INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MIN, INITIAL_DISCRETE_INPUTS_ADDRESS_RANGE_MAX);
			AddressRange holdingRegistersAddressRange = AddressRange(INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MIN, INITIAL_HOLDING_REGISTERS_ADDRESS_RANGE_MAX);
			AddressRange inputRegistersAddressRange = AddressRange(INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MIN, INITIAL_INPUT_REGISTERS_ADDRESS_RANGE_MAX);
			mutable QReadWriteLock lock;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
