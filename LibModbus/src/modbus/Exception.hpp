#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_EXCEPTION_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_EXCEPTION_HPP

#include "../platform.hpp"

#include <QException>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API Exception:
	public QException
{
	public:
		Exception(const QString & what);

		void raise() const override;

		Exception * clone() const override;

		const char * what() const noexcept override;

	private:
		const QByteArray m_what;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
