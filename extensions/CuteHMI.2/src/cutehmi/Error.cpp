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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
