#ifndef INCLUDECUTEHMIMODBUSINTERNALDISCRETEINPUTPOLLING_HPP
#define INCLUDECUTEHMIMODBUSINTERNALDISCRETEINPUTPOLLING_HPP

#include "common.hpp"
#include "DataContainerPolling.hpp"

class QUuid;

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE DiscreteInputPolling:
	public DataContainerPolling<DiscreteInputPolling, DiscreteInput>
{
		typedef DataContainerPolling<DiscreteInputPolling, DiscreteInput> Parent;

	public:
		DiscreteInputPolling(AbstractDevice * device, QUuid * requestId);

		const DataContainer & container() const;

		const Data * dataAt(quint16 address) const;

		void requestReadData(quint16 address, quint16 amount, QUuid * requestId);

		int maxRead() const;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALHOLDINGREGISTERPOLLING_HPP
