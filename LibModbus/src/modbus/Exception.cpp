#include "Exception.hpp"

namespace cutehmi {
namespace modbus {

Exception::Exception(const QString & what):
	m_what(what.toLocal8Bit())
{
}

void Exception::raise() const
{
	throw *this;
}

Exception * Exception::clone() const
{
	return new Exception(*this);
}

const char * Exception::what() const noexcept
{
	return m_what.constData();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
