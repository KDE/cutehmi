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

//<Doxygen-3.workaround target="Doxygen" cause="missing">
#ifdef DOXYGEN_WORKAROUND

namespace CuteHMI {
namespace Modbus {

/**
 * Exposes cutehmi::modbus::AbstractRegisterController to QML.
 */
class AbstractRegisterController: public cutehmi::modbus::AbstractRegisterController {};

/**
 * Exposes cutehmi::modbus::Register16Controller to QML.
 */
class Register16Controller: public cutehmi::modbus::Register16Controller {};

/**
 * Exposes cutehmi::modbus::CoilController to QML.
 */
class CoilController: public cutehmi::modbus::CoilController {};

/**
 * Exposes cutehmi::modbus::HoldingRegisterController to QML.
 */
class HoldingRegisterController: public cutehmi::modbus::HoldingRegisterController {};

/**
 * Exposes cutehmi::modbus::DiscreteInputController to QML.
 */
class DiscreteInputController: public cutehmi::modbus::DiscreteInputController {};

/**
 * Exposes cutehmi::modbus::InputRegisterController to QML.
 */
class InputRegisterController: public cutehmi::modbus::InputRegisterController {};

/**
 * Exposes cutehmi::modbus::AbstractDevice to QML.
 */
class AbstractDevice: public cutehmi::modbus::AbstractDevice {};

/**
 * Exposes cutehmi::modbus::AbstractClient to QML.
 */
class AbstractClient: public cutehmi::modbus::AbstractClient {};

/**
 * Exposes cutehmi::modbus::AbstractServer to QML.
 */
class AbstractServer: public cutehmi::modbus::AbstractServer {};

/**
 * Exposes cutehmi::modbus::DummyClient to QML.
 */
class DummyClient: public cutehmi::modbus::DummyClient {};

/**
 * Exposes cutehmi::modbus::TCPClient to QML.
 */
class TCPClient: public cutehmi::modbus::TCPClient {};

/**
 * Exposes cutehmi::modbus::TCPServer to QML.
 */
class TCPServer: public cutehmi::modbus::TCPServer {};

/**
 * Exposes cutehmi::modbus::RTUClient to QML.
 */
class RTUClient: public cutehmi::modbus::RTUClient {};

/**
 * Exposes cutehmi::modbus::RTUServer to QML.
 */
class RTUServer: public cutehmi::modbus::RTUServer {};

}
}

#endif
//</Doxygen-3.workaround>

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

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
