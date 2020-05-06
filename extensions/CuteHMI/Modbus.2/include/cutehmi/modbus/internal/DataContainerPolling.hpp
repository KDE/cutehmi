#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DATACONTAINERPOLLING_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DATACONTAINERPOLLING_HPP

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
	m_it = typename DataContainer::KeysIterator(& derived().container());
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


#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
