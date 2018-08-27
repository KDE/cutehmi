import qbs

import cutehmi

cutehmi.QMLExtension {
	name: "CuteHMI.Modbus"

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "Modbus QML"

	description: "QML components for dealing with Modbus protocol."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "CoilItem.js",
        "CoilItem.qml",
        "DiscreteInputItem.qml",
        "HoldingRegisterItem.js",
        "HoldingRegisterItem.qml",
        "InputRegisterItem.qml",
        "designer/CoilItemSpecifics.qml",
        "designer/DiscreteInputItemSpecifics.qml",
        "designer/HoldingRegisterItemSpecifics.qml",
        "designer/InputRegisterItemSpecifics.qml",
        "designer/Modbus.metainfo",
        "qmldir",
        "src/CuteHMIModbusQMLPlugin.cpp",
        "src/CuteHMIModbusQMLPlugin.hpp",
        "src/cutehmi/modbus/qml/CoilController.cpp",
        "src/cutehmi/modbus/qml/CoilController.hpp",
        "src/cutehmi/modbus/qml/DiscreteInputController.cpp",
        "src/cutehmi/modbus/qml/DiscreteInputController.hpp",
        "src/cutehmi/modbus/qml/HoldingRegisterController.cpp",
        "src/cutehmi/modbus/qml/HoldingRegisterController.hpp",
        "src/cutehmi/modbus/qml/InputRegisterController.cpp",
        "src/cutehmi/modbus/qml/InputRegisterController.hpp",
    ]

	//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_modbus_1" }
	cutehmi_modbus_1.reqMinor: 0
	//</workaround>
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
