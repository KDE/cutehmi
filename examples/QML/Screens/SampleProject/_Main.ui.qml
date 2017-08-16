import QtQuick 2.5
import QtQuick.Controls 2.1

import CuteHMI.Base 1.0
import CuteHMI.Modbus 1.0

Page {

	// Number display is provided by CuteHMI.Base module and it's best suited for showing fixed-point numbers with unit.
	NumberDisplay {
		id: numberDisplay
		x: 48
		y: 352
		font.pointSize: 16

		// HoldingRegisterItem is provided by CuteHMI.Modbus module. It synchronizes delegate (parent item by default)
		// with data held in holding registry of the specified modbus device.
		// By default HoldingRegistryItem uses "value" as delegate's property to be checked and updated, but this can be changed
		// by specifying "delegateProperty" property value.
		HoldingRegisterItem {
			id: hrItem
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
			address: 100
			device: mbAA1 // This is the device exposed within 'SampleProject.cutehmi.xml' file to be available as QML context property.
			valueScale: 1.0
		}
	}

	Slider {
		id: slider
		x: 157
		y: 350
		from: 0
		to: 100
		live: false
		enabled: !hrItem2.busy

		HoldingRegisterItem {
			id: hrItem2
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
			address: 100
			device: mbAA1
			valueScale: 1.0
		}
	}

	CheckBox {
		id: checkBox
		x: 69
		y: 424
		enabled: !coilItem.busy

		// CoilItem works similar way to HoldingRegisterItem, except it operates on Modbus coils (additionaly CuteHMI.Modbus module provides also DiscreteInputItem and InputRegisterItem).
		CoilItem {
			id: coilItem
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
			device: mbAA1
			address: 100
		}
	}

	// NumberDisplay is not best suited for showing bool value, but using it here shows how its properties can be customized.
	NumberDisplay {
		x: 157
		y: 425
		font.pointSize: 16
		unit: ""
		fractionalWidth: 0
		integralWidth: 0

		CoilItem {
			id: coilItem2
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
			device: mbAA1
			address: 100
			delegateProperty: "value" // By default CoilItem tries to assing property "checked".
		}
	}

	Label {
		x: 229
		y: 438
		text: coilController.value ? "on" : "off"

		// CoilItem internally uses CoilController component. CoilController is not Item-based. It does not provide any visual indication.
		// Sometimes it is desired to use this raw component. Analogically HoldingRegisterController, DiscreteInputController, InputRegisterController can be used
		// to access holding registers, discrete inputs and input registers.
		CoilController {
			id: coilController
			device: mbAA1
			address: 100
		}
	}

	ServicesView {
		id: servicesView
		x: 36
		y: 23
	}
}
