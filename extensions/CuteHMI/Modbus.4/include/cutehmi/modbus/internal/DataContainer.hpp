#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DATACONTAINER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DATACONTAINER_HPP

#include <QReadWriteLock>

#include <array>
#include <algorithm>
#include <memory>
#include <list>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Data container.
 */
template <typename T, std::size_t N = 65536>
class DataContainer
{
		typedef std::array<T *, N> InternalContainer;
		friend class KeysIterator;

	public:
		typedef T value_type;
		typedef T & reference;
		typedef const T & const_reference;
		typedef T * pointer;
		typedef const T * const_pointer;
		// <Qt-Qt_5_11_2_Reference_Documentation-Qt_Core-Container_Classes-The_Container_Classes-QLinkedList_iterator_semantics.principle>
		// "Iterators pointing to an item in a QLinkedList remain valid as long as the item exists, whereas iterators to a QList can
		//	become invalid after any insertion or removal."
		typedef std::list<std::size_t> KeysContainer;
		// </Qt-Qt_5_11_2_Reference_Documentation-Qt_Core-Container_Classes-The_Container_Classes-QLinkedList_iterator_semantics.principle>

		static constexpr std::size_t ADDRESS_SPACE = N;

		/**
		 * Keys iterator. This is read-only, thread-safe version of keys container iterator. It shares lock with data container, so
		 * that it won't enter iterating function while items are being inserted or removed and vice versa.
		 */
		class KeysIterator
		{
			public:
				KeysIterator(const DataContainer<T, N> * container);

				bool hasNext() const;

				KeysContainer::value_type next();

				KeysContainer::value_type previous();

			private:
				mutable QReadWriteLock * m_lock;
				const KeysContainer * m_keysContainer;
				KeysContainer::const_iterator m_it;
		};

		DataContainer();

		/**
		 * Get container size.
		 * @return container size.
		 *
		 * @threadsafe
		 */
		constexpr std::size_t size() const noexcept;

		/**
		 * Get value at given index.
		 * @param i index.
		 * @return value existing at given index or @p nullptr if value does not exist.
		 *
		 * @see value().
		 *
		 * @threadsafe
		 */
		const T * at(std::size_t i) const;

		/**
		 * Get value at given index.
		 * @param i index.
		 * @return value existing at given index or @p nullptr if value does not exist.
		 *
		 * @see value().
		 *
		 * @threadsafe
		 */
		T * at(std::size_t i);

		/**
		 * Get value at given index. If value does not exist it will be default-constructed and inserted into the container.
		 * @param i index.
		 * @return value existing at given index or default-constructed value.
		 *
		 * @see at().
		 *
		 * @remark Even tho' this function inserts a value, key iterators remain valid after a call to this function.
		 *
		 * @threadsafe
		 */
		T * value(std::size_t i);

		/**
		 * Insert value.
		 * @param i index.
		 * @param value value to be inserted.
		 *
		 * @remark Even tho' this function inserts a value, key iterators remain valid after a call to this function.
		 *
		 * @threadsafe
		 */
		void insert(std::size_t i, T * value);

		/**
		 * Clear container. Sets all elements to nullptr. No deletion is performed.
		 *
		 * @remark This function is thread-safe although it invalidates all iterators.
		 *
		 * @threadsafe
		 */
		void clear();

		/**
		 * Delete container contents. Function deletes all non-null elements and sets all elements to nullptr.
		 *
		 * @remark This function is thread-safe although it invalidates all iterators.
		 *
		 * @threadsafe
		 */
		void free();

		/**
		 * Get keys container.
		 * @return keys container.
		 *
		 * @threadsafe
		 */
		const KeysContainer & keys() const;

	protected:
		QReadWriteLock & lock() const;

		void insertKey(std::size_t i);

		InternalContainer m_array;
		KeysContainer m_keys;
		mutable QReadWriteLock m_lock;
};

template <typename T, std::size_t N>
DataContainer<T, N>::KeysIterator::KeysIterator(const DataContainer<T, N> * container):
	m_lock(& container->lock()),
	m_keysContainer(& container->keys()),
	m_it(container->keys().begin())
{
}

template <typename T, std::size_t N>
bool DataContainer<T, N>::KeysIterator::hasNext() const
{
	QReadLocker locker(m_lock);

	return m_it != m_keysContainer->end();
}

template <typename T, std::size_t N>
typename DataContainer<T, N>::KeysContainer::value_type DataContainer<T, N>::KeysIterator::next()
{
	QReadLocker locker(m_lock);

	return *(m_it)++;
}

template <typename T, std::size_t N>
typename DataContainer<T, N>::KeysContainer::value_type DataContainer<T, N>::KeysIterator::previous()
{
	QReadLocker locker(m_lock);

	return *(--m_it);
}

template <typename T, std::size_t N>

DataContainer<T, N>::DataContainer():
	m_array()
{
}

template <typename T, std::size_t N>
constexpr std::size_t DataContainer<T, N>::size() const noexcept
{
	// <cppreference.com-C++-Containers_library-Thread_safety-2.principle>
	// "2. All const member functions can be called concurrently by different threads on the same container."
	//	                                                                              -- https://en.cppreference.com/w/cpp/container
	return m_array.size();
	// </cppreference.com-C++-Containers_library-Thread_safety-2.principle>
}

template <typename T, std::size_t N>
const T * DataContainer<T, N>::at(std::size_t i) const
{
	QReadLocker locker(& m_lock);

	return m_array.at(i);
}

template <typename T, std::size_t N>
T * DataContainer<T, N>::at(std::size_t i)
{
	QReadLocker locker(& m_lock);

	return m_array.at(i);
}

template <typename T, std::size_t N>
T * DataContainer<T, N>::value(std::size_t i)
{
	T * result;

	{
		QReadLocker readLocker(& m_lock);

		result = m_array.at(i);
	}

	if (result == nullptr) {
		QWriteLocker writeLocker(& m_lock);

		// In a meanwhile value may have been created from another thread, so perform a lookup again - this time it is serialized by write locker.
		result = m_array.at(i);

		if (result == nullptr) {
			result = new T;
			m_array[i] = result;
			insertKey(i);
		}
	}

	return result;
}

template <typename T, std::size_t N>
void DataContainer<T, N>::insert(std::size_t i, T * value)
{
	QWriteLocker locker(& m_lock);

	m_array[i] = value;
	insertKey(i);
}

template <typename T, std::size_t N>
void DataContainer<T, N>::clear()
{
	QWriteLocker locker(& m_lock);

	m_keys.clear();

	std::fill(m_array.begin(), m_array.end(), nullptr);
}

template <typename T, std::size_t N>
void DataContainer<T, N>::free()
{
	QWriteLocker locker(& m_lock);

	for (typename DataContainer<T, N>::KeysContainer::const_iterator it = keys().begin(); it != keys().end(); ++it)
		delete m_array.at(*it);

	m_keys.clear();

	std::fill(m_array.begin(), m_array.end(), nullptr);
}

template <typename T, std::size_t N>
const typename DataContainer<T, N>::KeysContainer & DataContainer<T, N>::keys() const
{
	return m_keys;
}

template <typename T, std::size_t N>
QReadWriteLock & DataContainer<T, N>::lock() const
{
	return m_lock;
}

template <typename T, std::size_t N>
void DataContainer<T, N>::insertKey(std::size_t i)
{
	KeysContainer::iterator it = m_keys.begin();
	while (it != m_keys.end()) {
		if (*it < i)
			++it;
		else
			break;
	}

	m_keys.insert(it, i);
}

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
