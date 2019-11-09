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

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
