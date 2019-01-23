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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
