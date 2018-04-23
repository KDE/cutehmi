import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_modbus_1_qml"

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
		"plugins.qmltypes",
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

	//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_modbus_1" } cutehmi_modbus_1.version: "0.0"
	//</workaround>
}

