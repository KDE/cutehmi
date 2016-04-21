#ifndef DUMMYCONNECTION_H
#define DUMMYCONNECTION_H

#include "../platform.hpp"
#include "AbstractConnection.hpp"

#include <QString>

namespace cutehmi {
namespace modbus {

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

		bool connect() override;

		void disconnect() override;

		int readIr(int addr, int num, uint16_t * dst) override;

		int readR(int addr, int num, uint16_t * dst) override;

		int writeR(int addr, uint16_t value) override;

		int readIb(int addr, int num, uint8_t * dst) override;

		int readB(int addr, int num, uint8_t * dst) override;

		int writeB(int addr, bool value) override;

	private:
		bool m_connected;
		unsigned long m_latency;
		uint16_t m_rArr[ADDR_SPACE_SIZE];
		uint16_t m_irArr[ADDR_SPACE_SIZE];
		uint8_t m_bArr[ADDR_SPACE_SIZE];
		uint8_t m_ibArr[ADDR_SPACE_SIZE];
};

}
}

#endif // DUMMYCONNECTION_H
