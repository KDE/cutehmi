#ifndef H_QML_CUTEHMI_MODBUS_SRC_CUTEHMI_MODBUS_QML_DISCRETEINPUTCONTROLLER_HPP
#define H_QML_CUTEHMI_MODBUS_SRC_CUTEHMI_MODBUS_QML_DISCRETEINPUTCONTROLLER_HPP

#include "internal/common.hpp"
#include "Register1Controller.hpp"

#include <QObject>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API DiscreteInputController:
	public Register1Controller
{
		Q_OBJECT

	public:
		DiscreteInputController(QObject * parent = nullptr);

	protected:
		Register1 * registerAt(quint16 address) const override;

		void requestReadRegisters(quint16 address, quint16 amount, QUuid * requestId) const override;

		void requestWriteRegister(quint16 address, bool value, QUuid * requestId) const override;

		AbstractDevice::Function readRegistersFunction() const override;

		AbstractDevice::Function writeRegisterFunction() const override;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
