#include "../../include/cutehmi/Exception.hpp"

namespace cutehmi {

Exception::Exception(const QString & what):
	m_whatArr(what.toLocal8Bit())
{
}

void Exception::raise() const noexcept(false)
{
	throw *this;
}

Exception * Exception::clone() const
{
	return new Exception(*this);
}

const char * Exception::what() const noexcept
{
	return m_whatArr.constData();
}

}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
