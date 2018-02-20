#ifndef CUTEHMI_CUTEHMI__MODBUS__1__LIB_INCLUDE_MODBUS_INTERNAL_DATACONTAINER_HPP
#define CUTEHMI_CUTEHMI__MODBUS__1__LIB_INCLUDE_MODBUS_INTERNAL_DATACONTAINER_HPP

#include "common.hpp"

#include <QLinkedList>
#include <QReadWriteLock>

#include <array>
#include <algorithm>

namespace cutehmi {
namespace modbus {
namespace internal {

template <typename T, std::size_t N = 65536>
class DataContainer
{
	typedef std::array<T, N> InternalContainer;
	friend class KeysIterator;

	public:
		typedef typename InternalContainer::iterator iterator;
		typedef typename InternalContainer::const_iterator const_iterator;
		typedef typename InternalContainer::reference reference;
		typedef typename InternalContainer::const_reference const_reference;
		typedef typename InternalContainer::value_type value_type;
		typedef QLinkedList<std::size_t> KeysContainer;

		/**
		 * Keys iterator. This is read-only thread-safe version of keys container iterator.
		 */
		class KeysIterator
		{
			public:
				KeysIterator(const DataContainer<T, N> & container);

				bool hasNext() const;

				KeysContainer::value_type next();

			private:
				mutable QReadLocker m_readLocker;
				QLinkedListIterator<KeysContainer::value_type> m_it;
		};

		DataContainer();

		constexpr std::size_t size() const noexcept;

		reference at(std::size_t i);

		const_reference at(std::size_t i) const;

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		iterator find(std::size_t i);

		const_iterator find(std::size_t i) const;

		iterator insert(std::size_t i, const value_type & value);

		/**
		 * Clear container. Sets all elements to nullptr. No deletion is performed.
		 */
		void clear();

		const KeysContainer & keys() const;

	protected:
		const QReadWriteLock & keysLock() const;

		QReadWriteLock & keysLock();

	private:
		InternalContainer m_array;
		KeysContainer m_keys;
		QReadWriteLock m_keysLock;
};

template<typename T, std::size_t N>
DataContainer<T, N>::KeysIterator::KeysIterator(const DataContainer<T, N> & container):
	m_readLocker(& const_cast<DataContainer<T, N> & >(container).keysLock()),
	m_it(container.keys())
{
	m_readLocker.unlock();
}

template<typename T, std::size_t N>
bool DataContainer<T, N>::KeysIterator::hasNext() const
{
	m_readLocker.relock();
	bool result = m_it.hasNext();
	m_readLocker.unlock();
	return result;
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::KeysContainer::value_type DataContainer<T, N>::KeysIterator::next()
{
	m_readLocker.relock();
	typename DataContainer<T, N>::KeysContainer::value_type result = m_it.next();
	m_readLocker.unlock();
	return result;
}

template<typename T, std::size_t N>
DataContainer<T, N>::DataContainer():
	m_array()
{
}

template<typename T, std::size_t N>
constexpr std::size_t DataContainer<T, N>::size() const noexcept
{
	return m_array.size();
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::reference DataContainer<T, N>::at(std::size_t i)
{
	return m_array.at(i);
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::const_reference DataContainer<T, N>::at(std::size_t i) const
{
	return m_array.at(i);
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::iterator DataContainer<T, N>::begin()
{
	return m_array.begin();
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::const_iterator DataContainer<T, N>::begin() const
{
	return m_array.begin();
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::iterator DataContainer<T, N>::end()
{
	return m_array.end();
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::const_iterator DataContainer<T, N>::end() const
{
	return m_array.end();
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::iterator DataContainer<T, N>::find(std::size_t i)
{
	if (m_array[i] == nullptr)
		return end();
	return & m_array[i];
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::const_iterator DataContainer<T, N>::find(std::size_t i) const
{
	if (m_array[i] == nullptr)
		return end();
	return & m_array[i];
}

template<typename T, std::size_t N>
typename DataContainer<T, N>::iterator DataContainer<T, N>::insert(std::size_t i, const value_type & value)
{
	m_array[i] = value;
	keysLock().lockForWrite();
	m_keys.append(i);
	keysLock().unlock();
	return & m_array[i];
}

template<typename T, std::size_t N>
void DataContainer<T, N>::clear()
{
	keysLock().lockForWrite();
	m_keys.clear();
	keysLock().unlock();
	std::fill(m_array.begin(), m_array.end(), nullptr);
}

template<typename T, std::size_t N>
const typename DataContainer<T, N>::KeysContainer & DataContainer<T, N>::keys() const
{
	return m_keys;
}

template<typename T, std::size_t N>
const QReadWriteLock & DataContainer<T, N>::keysLock() const
{
	return m_keysLock;
}

template<typename T, std::size_t N>
QReadWriteLock & DataContainer<T, N>::keysLock()
{
	return m_keysLock;
}

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
