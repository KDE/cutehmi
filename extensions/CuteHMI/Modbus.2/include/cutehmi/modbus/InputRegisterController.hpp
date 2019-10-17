#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INPUTREGISTERCONTROLLER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INPUTREGISTERCONTROLLER_HPP

#include "internal/common.hpp"
#include "Register16Controller.hpp"

#include <QObject>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API InputRegisterController:
	public Register16Controller
{
		Q_OBJECT
	public:
		InputRegisterController(QObject * parent = nullptr);

	protected:
		Register16 * registerAt(quint16 address) const override;

		void requestReadRegisters(quint16 address, quint16 amount, QUuid * requestId) const override;

		void requestWriteRegister(quint16 address, quint16 value, QUuid * requestId) const override;

		AbstractDevice::Function readRegistersFunction() const override;

		AbstractDevice::Function writeRegisterFunction() const override;
};

}
}

#endif
