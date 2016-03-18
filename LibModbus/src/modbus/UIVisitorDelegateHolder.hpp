#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_UIVISITORDELEGATEHOLDER_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_UIVISITORDELEGATEHOLDER_HPP

#include "../platform.hpp"

#include <QObject>

namespace cutehmi {

namespace widgets { class UIVisitorDelegate; }

namespace modbus {

class CUTEHMI_MODBUS_API UIVisitorDelegateHolder:
	public QObject
{
	public:
		virtual widgets::UIVisitorDelegate * uiDelegate() const;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
