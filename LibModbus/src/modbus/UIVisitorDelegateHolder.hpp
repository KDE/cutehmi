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
