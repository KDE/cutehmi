#include "Error.hpp"

namespace base {

Error::Error():
	code(UNINITIALIZED)
{
}

  Error::Error(int p_code):
	code(p_code)
{
}

Error::operator int() const
{
	return code;
}

bool Error::success() const
{
	return code == Error::OK;
}

QString Error::str() const
{
	switch (code) {
		case Error::OK:
			return tr("No error.");
		case Error::FAIL:
			return tr("Undescribed error.");
		case Error::UNINITIALIZED:
			return tr("Uninitialized error code.");
		default:
			return tr("Unrecognized error code.");
	}
}

}
