#ifndef DATACONTAINERPOLLING_HPP
#define DATACONTAINERPOLLING_HPP

#include "IterableTasks.hpp"

#include <cutehmi/modbus/AbstractDevice.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

template <class DERIVED, class DATA>
class DataContainerPolling:
	public IterableTasks
{
	public:
		typedef DATA Data;
		typedef typename RegisterTraits<Data>::Container DataContainer;

		DataContainerPolling(AbstractDevice * device, QUuid * requestId);

		AbstractDevice * device() const;

		bool runNext() override;

		void reset() override;

		DERIVED & derived();

		const DERIVED & derived() const;

	private:
		AbstractDevice * m_device;
		QUuid * m_requestId;
		typename DataContainer::KeysIterator m_it;
};

template<class DERIVED, class DATA>
DataContainerPolling<DERIVED, DATA>::DataContainerPolling(AbstractDevice * device, QUuid * requestId):
	m_device(device),
	m_requestId(requestId),
	m_it(& derived().container())
{
}

template<class DERIVED, class DATA>
AbstractDevice * DataContainerPolling<DERIVED, DATA>::device() const
{
	return m_device;
}

template<class DERIVED, class DATA>
bool DataContainerPolling<DERIVED, DATA>::runNext()
{
	int maxRead = derived().maxRead();
	quint16 startAddress = 0;
	quint16 count = 0;

	// Find address of next wakefull register, if any. Value of 'count' set to '1' indicates that such register has been found.
	while (m_it.hasNext()) {
		quint16 address = static_cast<quint16>(m_it.next());
		typename DataContainer::const_pointer data = derived().dataAt(address);
		if (data && data->wakeful()) {
			startAddress = address;
			count = 1;
			break;
		}
	}

	if (count) {

		// Check if more registers can be read in the same request.
		while (m_it.hasNext()) {
			quint16 address = static_cast<quint16>(m_it.next());
			if ((address - startAddress) < maxRead) {
				typename DataContainer::const_pointer data = derived().dataAt(address);
				if (data && data->wakeful())
					count = address - startAddress + 1;
			} else {
				m_it.previous();
				break;
			}
		}

		derived().requestReadData(startAddress, count, m_requestId);

		return true;
	} else
		return false;
}

template<class DERIVED, class DATA>
void DataContainerPolling<DERIVED, DATA>::reset()
{
	m_it = DataContainer::KeysIterator(& derived().container());
}

template<class DERIVED, class DATA>
DERIVED & DataContainerPolling<DERIVED, DATA>::derived()
{
	return static_cast<DERIVED &>(*this);
}

template<class DERIVED, class DATA>
const DERIVED & DataContainerPolling<DERIVED, DATA>::derived() const
{
	return static_cast<const DERIVED &>(*this);
}


}
}
}


#endif // CONTAINERBASEDPOLLING_HPP
