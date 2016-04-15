#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <cstdint>

namespace cutehmi {
namespace modbus {

class AbstractConnection
{
	public:
		virtual ~AbstractConnection() = default;

		virtual bool connect() = 0;

		virtual void disconnect() = 0;

		virtual int readIr(int addr, int num, uint16_t & dest) = 0;

		virtual int readR(int addr, int num, uint16_t & dest) = 0;

		virtual int writeR(int addr, uint16_t value) = 0;

	protected:
		AbstractConnection() = default;
};

}
}

#endif // ICONNECTION_H
