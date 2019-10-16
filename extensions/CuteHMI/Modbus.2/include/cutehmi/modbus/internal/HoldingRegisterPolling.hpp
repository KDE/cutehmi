#ifndef INCLUDECUTEHMIMODBUSINTERNALHOLDINGREGISTERPOLLING_HPP
#define INCLUDECUTEHMIMODBUSINTERNALHOLDINGREGISTERPOLLING_HPP

#include "common.hpp"
//#include "IterableTasks.hpp"
#include "DataContainerPolling.hpp"

class QUuid;

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE HoldingRegisterPolling:
	public DataContainerPolling<HoldingRegisterPolling, HoldingRegister>
{
		typedef DataContainerPolling<HoldingRegisterPolling, HoldingRegister> Parent;

	public:
		HoldingRegisterPolling(AbstractDevice * device, QUuid * requestId);

		const DataContainer & container() const;

		const Data * dataAt(quint16 address) const;

		void requestReadData(quint16 address, quint16 amount, QUuid * requestId);

		int maxRead() const;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALHOLDINGREGISTERPOLLING_HPP
