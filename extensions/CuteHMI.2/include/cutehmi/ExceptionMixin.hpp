#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_EXCEPTIONMIXIN_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_EXCEPTIONMIXIN_HPP

#include "Exception.hpp"

#include <QCoreApplication>
#include <QString>

namespace cutehmi {

/**
 * %Exception mixin. This class template can be used to automatically reimplement raise() and clone() methods for DERIVED class.
 * This is internally achieved through static polymorphism technique.
 */
template <class DERIVED>
class ExceptionMixin:
	public Exception
{
	public:
		explicit ExceptionMixin(const QString & what);

		void raise() const noexcept(false) override;

		Exception * clone() const override;
};

template <class DERIVED>
ExceptionMixin<DERIVED>::ExceptionMixin(const QString & what):
	Exception(what)
{
}

template <class DERIVED>
void ExceptionMixin<DERIVED>::raise() const noexcept(false)
{
	throw *(static_cast<const DERIVED *>(this));
}

template <class DERIVED>
Exception * ExceptionMixin<DERIVED>::clone() const
{
	return new DERIVED(static_cast<const DERIVED &>(*this));
}

}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
