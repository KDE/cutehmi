import QtQuick 2.5
import QtQuick.Controls 2.2

import CuteHMI 1.0
import CuteHMI.Modbus 1.0

Page
{
	padding: 20

	// Number display is provided by CuteHMI.Base module and it's best suited for showing fixed-point numbers with unit.

	// NumberDisplay is not best suited for showing bool value, but using it here shows how its properties can be customized.
	Column {
		id: column
		spacing: 20
		anchors.centerIn: parent

		ServicesView {
			id: servicesView
		}

		Row {
			id: coilRow
			spacing: 20

			CheckBox {
				id: coilCheckBox
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

			Label {
				id: coilLabel
				height: parent.height
				text: coilController.value ? "on" : "off"
				font.pointSize: 12
				verticalAlignment: Text.AlignVCenter

				// CoilItem internally uses CoilController component. CoilController is not Item-based. It does not provide any visual indication.
				// Sometimes it is desired to use this raw component. Analogically HoldingRegisterController, DiscreteInputController, InputRegisterController can be used
				// to access holding registers, discrete inputs and input registers.
				CoilController {
					id: coilController
					device: mbAA1
					address: 100
				}
			}

			NumberDisplay {
				id: coilNumberDisplay
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
		}

		Row {
			id: hrRow

			Slider {
				id: hrSlider
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

			NumberDisplay {
				id: hrNumberDisplay
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
		}
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
