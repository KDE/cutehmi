#ifndef H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCONNECTION_HPP
#define H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCONNECTION_HPP

#include "common.hpp"
#include "AbstractConnection.hpp"

#include <QString>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Dummy connection.
 */
class CUTEHMI_MODBUS_API DummyConnection:
	public AbstractConnection
{
	public:
		static const int ADDR_SPACE_SIZE = 65536;

		DummyConnection();

		void setLatency(unsigned long latency);

		unsigned long latency() const;

		void setConnectLatency(unsigned long latency);

		unsigned long connectLatency() const;

		void setDisconnectLatency(unsigned long latency);

		unsigned long disconnectLatency() const;

		bool connect() override;

		void disconnect() override;

		bool connected() const override;

		int readIr(int addr, int num, uint16_t * dest) override;

		int readR(int addr, int num, uint16_t * dest) override;

		int writeR(int addr, uint16_t value) override;

		int readIb(int addr, int num, bool * dest) override;

		int readB(int addr, int num, bool * dest) override;

		int writeB(int addr, bool value) override;

	private:
		struct Members
		{
			bool connected;
			unsigned long latency;
			unsigned long connectLatency;
			unsigned long disconnectLatency;
			uint16_t rArr[ADDR_SPACE_SIZE];
			uint16_t irArr[ADDR_SPACE_SIZE];
			bool bArr[ADDR_SPACE_SIZE];
			bool ibArr[ADDR_SPACE_SIZE];

			Members():
				connected(false),
				latency(0),
				connectLatency(0),
				disconnectLatency(0),
				rArr(),
				irArr(),
				bArr(),
				ibArr()
			{
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
