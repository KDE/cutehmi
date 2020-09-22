#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_MPTR_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_MPTR_HPP

#include <memory>

// Friend functions outside the 'cutehmi' namespace have to be forward declared before making them friend.

namespace cutehmi { template<class T, class DELETER = std::default_delete<T>> class MPtr; }

template <class TL, class DL, class TR, class DR>
bool operator ==(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL>
bool operator ==(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

template <class TR, class DR>
bool operator ==(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL, class TR, class DR>
bool operator !=(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL>
bool operator !=(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

template <class TR, class DR>
bool operator !=(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL, class TR, class DR>
bool operator <(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL>
bool operator <(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

template <class TR, class DR>
bool operator <(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL, class TR, class DR>
bool operator <=(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL>
bool operator <=(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

template <class TR, class DR>
bool operator <=(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL, class TR, class DR>
bool operator >(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL>
bool operator >(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

template <class TR, class DR>
bool operator >(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL, class TR, class DR>
bool operator >=(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TL, class DL>
bool operator >=(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

template <class TR, class DR>
bool operator >=(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept;

template <class TS, class DS>
void swap(cutehmi::MPtr<TS, DS> & x, cutehmi::MPtr<TS, DS> & y) noexcept;

namespace cutehmi {

/**
 * Members pointer. This class wraps std::unique_ptr and provides opaque interface that forwards const to the member.
 */
template<class T, class DELETER>
class MPtr: private std::unique_ptr<T, DELETER>
{
	typedef std::unique_ptr<T, DELETER> Parent;

	template <class TL, class DL, class TR, class DR>
	friend bool ::operator ==(const MPtr<TL, DL> & lhs, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL>
	friend bool ::operator ==(const MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

	template <class TR, class DR>
	friend bool ::operator ==(std::nullptr_t, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL, class TR, class DR>
	friend bool ::operator !=(const MPtr<TL, DL> & lhs, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL>
	friend bool ::operator !=(const MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

	template <class TR, class DR>
	friend bool ::operator !=(std::nullptr_t, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL, class TR, class DR>
	friend bool ::operator <(const MPtr<TL, DL> & lhs, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL>
	friend bool ::operator <(const MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

	template <class TR, class DR>
	friend bool ::operator <(std::nullptr_t, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL, class TR, class DR>
	friend bool ::operator <=(const MPtr<TL, DL> & lhs, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL>
	friend bool ::operator <=(const MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

	template <class TR, class DR>
	friend bool ::operator <=(std::nullptr_t, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL, class TR, class DR>
	friend bool ::operator >(const MPtr<TL, DL> & lhs, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL>
	friend bool ::operator >(const MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

	template <class TR, class DR>
	friend bool ::operator >(std::nullptr_t, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL, class TR, class DR>
	friend bool ::operator >=(const MPtr<TL, DL> & lhs, const MPtr<TR, DR> & rhs) noexcept;

	template <class TL, class DL>
	friend bool ::operator >=(const MPtr<TL, DL> & lhs, std::nullptr_t) noexcept;

	template <class TR, class DR>
	friend bool ::operator >=(std::nullptr_t, const MPtr<TR, DR> & rhs) noexcept;

	template <class TS, class DS>
	friend void ::swap(MPtr<TS, DS> & x, MPtr<TS, DS> & y) noexcept;

	public:
		typedef T element_type;
		typedef T * pointer;
		typedef const T * const_pointer;
		typedef typename Parent::deleter_type deleter_type;
		typedef typename std::add_lvalue_reference<element_type>::type reference;
		typedef typename std::add_lvalue_reference<typename std::add_const<element_type>::type>::type const_reference;

		using Parent::Parent;

		using Parent::operator bool;

		using Parent::get_deleter;

		using Parent::release;

		using Parent::reset;

		void swap(MPtr<T, DELETER> & x) noexcept
		{
			Parent::swap(x);
		}

		const_pointer get() const noexcept
		{
			return Parent::get();
		}

		pointer get() noexcept
		{
			return Parent::get();
		}

		const_pointer operator->() const noexcept
		{
			return Parent::operator->();
		}

		pointer operator->() noexcept
		{
			return Parent::operator->();
		}

		reference operator *()
		{
			return Parent::operator *();
		}

		const_reference operator *() const
		{
			return Parent::operator *();
		}
};

}

template <class TL, class DL, class TR, class DR>
bool operator ==(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator ==(static_cast<const std::unique_ptr<TL, DL> & >(lhs), static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL>
bool operator ==(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept
{
	return operator ==(static_cast<const std::unique_ptr<TL, DL> & >(lhs), nullptr);
}

template <class TR, class DR>
bool operator ==(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator ==(nullptr, static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL, class TR, class DR>
bool operator !=(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator !=(static_cast<const std::unique_ptr<TL, DL> & >(lhs), static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL>
bool operator !=(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept
{
	return operator !=(static_cast<const std::unique_ptr<TL, DL> & >(lhs), nullptr);
}

template <class TR, class DR>
bool operator !=(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator !=(nullptr, static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL, class TR, class DR>
bool operator <(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator <(static_cast<const std::unique_ptr<TL, DL> & >(lhs), static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL>
bool operator <(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept
{
	return operator <(static_cast<const std::unique_ptr<TL, DL> & >(lhs), nullptr);
}

template <class TR, class DR>
bool operator <(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator <(nullptr, static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL, class TR, class DR>
bool operator <=(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator <=(static_cast<const std::unique_ptr<TL, DL> & >(lhs), static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL>
bool operator <=(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept
{
	return operator <=(static_cast<const std::unique_ptr<TL, DL> & >(lhs), nullptr);
}

template <class TR, class DR>
bool operator <=(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator <=(nullptr, static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL, class TR, class DR>
bool operator >(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator >(static_cast<const std::unique_ptr<TL, DL> & >(lhs), static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL>
bool operator >(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept
{
	return operator >(static_cast<const std::unique_ptr<TL, DL> & >(lhs), nullptr);
}

template <class TR, class DR>
bool operator >(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator >(nullptr, static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL, class TR, class DR>
bool operator >=(const cutehmi::MPtr<TL, DL> & lhs, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator >=(static_cast<const std::unique_ptr<TL, DL> & >(lhs), static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TL, class DL>
bool operator >=(const cutehmi::MPtr<TL, DL> & lhs, std::nullptr_t) noexcept
{
	return operator >=(static_cast<const std::unique_ptr<TL, DL> & >(lhs), nullptr);
}

template <class TR, class DR>
bool operator >=(std::nullptr_t, const cutehmi::MPtr<TR, DR> & rhs) noexcept
{
	return operator >=(nullptr, static_cast<const std::unique_ptr<TR, DR> & >(rhs));
}

template <class TS, class DS>
void swap(cutehmi::MPtr<TS, DS> & x, cutehmi::MPtr<TS, DS> & y) noexcept
{
	swap(static_cast<const std::unique_ptr<TS, DS> &>(x), static_cast<const std::unique_ptr<TS, DS> &>(y));
}

#endif

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
