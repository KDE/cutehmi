#include "../../include/cutehmi/Error.hpp"

namespace cutehmi {

Error::Error():
	m_code(UNINITIALIZED)
{
}

Error::Error(int code):
	m_code(code)
{
}

bool Error::operator ==(const Error & other) const
{
	return m_code == other.m_code;
}

bool Error::operator !=(const Error & other) const
{
	return m_code != other.m_code;
}

Error::operator bool() const
{
	return m_code == Error::OK;
}

int Error::code() const
{
	return m_code;
}

QString Error::str() const
{
	switch (code()) {
		case Error::OK:
			return tr("No error.");
		case Error::FAIL:
			return tr("Undescribed error.");
		case Error::UNINITIALIZED:
			return tr("Uninitialized error code.");
		default:
			return tr("Unrecognized error code: %1.").arg(code());
	}
}

void Error::setCode(int code)
{
	m_code = code;
}

}

bool operator ==(const cutehmi::Error & error, int code)
{
	return error.code() == code;
}

bool operator ==(int code, const cutehmi::Error & error)
{
	return error.code() == code;
}

bool operator !=(const cutehmi::Error & error, int code)
{
	return error.code() != code;
}

bool operator !=(int code, const cutehmi::Error & error)
{
	return error.code() != code;
}
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
