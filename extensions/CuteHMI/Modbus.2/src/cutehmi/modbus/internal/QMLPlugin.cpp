#include "QMLPlugin.hpp"

#include <cutehmi/modbus/TCPServer.hpp>
#include <cutehmi/modbus/TCPClient.hpp>
#include <cutehmi/modbus/RTUClient.hpp>
#include <cutehmi/modbus/RTUServer.hpp>
#include <cutehmi/modbus/DummyClient.hpp>
#include <cutehmi/modbus/CoilController.hpp>
#include <cutehmi/modbus/HoldingRegisterController.hpp>
#include <cutehmi/modbus/DiscreteInputController.hpp>
#include <cutehmi/modbus/InputRegisterController.hpp>

#include <QtQml>

namespace CuteHMI {
namespace Modbus {

/**
 * @class CuteHMI::Modbus::AbstractRegisterController
 * Exposes cutehmi::modbus::AbstractRegisterController to QML.
 */

/**
 * @class CuteHMI::Modbus::Register16Controller
 * Exposes cutehmi::modbus::Register16Controller to QML.
 */

/**
 * @class CuteHMI::Modbus::CoilController
 * Exposes cutehmi::modbus::CoilController to QML.
 */

/**
 * @class CuteHMI::Modbus::HoldingRegisterController
 * Exposes cutehmi::modbus::HoldingRegisterController to QML.
 */

/**
 * @class CuteHMI::Modbus::DiscreteInputController
 * Exposes cutehmi::modbus::DiscreteInputController to QML.
 */

/**
 * @class CuteHMI::Modbus::InputRegisterController
 * Exposes cutehmi::modbus::InputRegisterController to QML.
 */

/**
 * @class CuteHMI::Modbus::AbstractDevice
 * Exposes cutehmi::modbus::AbstractDevice to QML.
 */

/**
 * @class CuteHMI::Modbus::AbstractClient
 * Exposes cutehmi::modbus::AbstractClient to QML.
 */

/**
 * @class CuteHMI::Modbus::AbstractServer
 * Exposes cutehmi::modbus::AbstractServer to QML.
 */

/**
 * @class CuteHMI::Modbus::DummyClient
 * Exposes cutehmi::modbus::DummyClient to QML.
 */

/**
 * @class CuteHMI::Modbus::TCPClient
 * Exposes cutehmi::modbus::TCPClient to QML.
 */

/**
 * @class CuteHMI::Modbus::TCPServer
 * Exposes cutehmi::modbus::TCPServer to QML.
 */

/**
 * @class CuteHMI::Modbus::RTUClient
 * Exposes cutehmi::modbus::RTUClient to QML.
 */

/**
 * @class CuteHMI::Modbus::RTUServer
 * Exposes cutehmi::modbus::RTUServer to QML.
 */

}
}

namespace cutehmi {
namespace modbus {
namespace internal {

void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Modbus"));

	qmlRegisterUncreatableType<cutehmi::modbus::AbstractRegisterController>(uri, CUTEHMI_MODBUS_MAJOR, 0, "AbstractRegisterController", "Class 'cutehmi::modbus::AbstractRegisterController' is abstract and it can not be instantiated from QML.");
	qmlRegisterUncreatableType<cutehmi::modbus::Register16Controller>(uri, CUTEHMI_MODBUS_MAJOR, 0, "Register16Controller", "Class 'cutehmi::modbus::Register16Controller' is abstract and it can not be instantiated from QML.");
	qmlRegisterUncreatableType<cutehmi::modbus::Register1Controller>(uri, CUTEHMI_MODBUS_MAJOR, 0, "Register1Controller", "Class 'cutehmi::modbus::Register1Controller' is abstract and it can not be instantiated from QML.");
	qmlRegisterType<cutehmi::modbus::CoilController>(uri, CUTEHMI_MODBUS_MAJOR, 0, "CoilController");
	qmlRegisterType<cutehmi::modbus::HoldingRegisterController>(uri, CUTEHMI_MODBUS_MAJOR, 0, "HoldingRegisterController");
	qmlRegisterType<cutehmi::modbus::DiscreteInputController>(uri, CUTEHMI_MODBUS_MAJOR, 0, "DiscreteInputController");
	qmlRegisterType<cutehmi::modbus::InputRegisterController>(uri, CUTEHMI_MODBUS_MAJOR, 0, "InputRegisterController");

	qmlRegisterUncreatableType<cutehmi::modbus::AbstractDevice>(uri, CUTEHMI_MODBUS_MAJOR, 0, "AbstractDevice", "Class 'cutehmi::modbus::AbstractDevice' is abstract and its instance can not be created from QML.");
	qmlRegisterUncreatableType<cutehmi::modbus::AbstractClient>(uri, CUTEHMI_MODBUS_MAJOR, 0, "AbstractClient", "Class 'cutehmi::modbus::AbstractClient' is abstract and its instance can not be created from QML.");
	qmlRegisterUncreatableType<cutehmi::modbus::AbstractServer>(uri, CUTEHMI_MODBUS_MAJOR, 0, "AbstractServer", "Class 'cutehmi::modbus::AbstractServer' is abstract and its instance can not be created from QML.");

	qmlRegisterType<cutehmi::modbus::DummyClient>(uri, CUTEHMI_MODBUS_MAJOR, 0, "DummyClient");
	qmlRegisterType<cutehmi::modbus::TCPClient>(uri, CUTEHMI_MODBUS_MAJOR, 0, "TCPClient");
	qmlRegisterType<cutehmi::modbus::TCPServer>(uri, CUTEHMI_MODBUS_MAJOR, 0, "TCPServer");
	qmlRegisterType<cutehmi::modbus::RTUClient>(uri, CUTEHMI_MODBUS_MAJOR, 0, "RTUClient");
	qmlRegisterType<cutehmi::modbus::RTUServer>(uri, CUTEHMI_MODBUS_MAJOR, 0, "RTUServer");
}

}
}
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
