#ifndef H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_MPTR_HPP
#define H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_MPTR_HPP

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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
