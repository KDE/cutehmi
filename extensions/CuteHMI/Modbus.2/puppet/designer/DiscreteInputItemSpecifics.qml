import QtQuick 2.0
import HelperWidgets 2.0
import QtQuick.Layouts 1.0

Column {
	anchors.left: parent.left
	anchors.right: parent.right

	Section {
		anchors.left: parent.left
		anchors.right: parent.right
		caption: "Modbus"

		SectionLayout {
			rows: 2

			Label {
				text: qsTr("Device")
			}

			SecondColumnLayout {
				//<workaround.puppet.CuteHMI.Modbus-1 target="QtCreator" cause="missing">
				// Using Label instead of
				//	placeholderText: backendValue.expression
				// Placeholder text is not visible. Hiding LineEdit by setting maximum width to 'actionIndicator.width'.
				LineEdit {
					id: deviceLineEdit

					backendValue: backendValues.device
					Layout.maximumWidth: actionIndicator.width
					showExtendedFunctionButton: true
					showTranslateCheckBox: false
					readOnly: true
				}

				Label {
					text: deviceLineEdit.backendValue.expression
					Layout.fillWidth: true
				}
				//</workaround.puppet.CuteHMI.Modbus-1>
			}

			Label {
				text: qsTr("Address")
			}

			SecondColumnLayout {
				SpinBox {
					backendValue: backendValues.address
					minimumValue: 0
					maximumValue: 65535
					Layout.preferredWidth: 80
				}

				Item {
					width: 4
					height: 4
				}

				Label {
					width: 120
					tooltip: "Modbus convention"
					text: "(" + (backendValues.address.value + 100001) + ")"
				}
			}

			Label {
				text: qsTr("Delegate")
			}

			SecondColumnLayout {
				//<workaround.puppet.CuteHMI.Modbus-1 target="QtCreator" cause="missing">
				// Using Label instead of
				//	placeholderText: backendValue.expression
				// Placeholder text is not visible. Hiding LineEdit by setting maximum width to 'actionIndicator.width'.
				LineEdit {
					id: delegateLineEdit

					backendValue: backendValues.delegate
					Layout.maximumWidth: actionIndicator.width
					showExtendedFunctionButton: true
					showTranslateCheckBox: false
					readOnly: true
				}

				Label {
					text: delegateLineEdit.backendValue.expression ? delegateLineEdit.backendValue.expression : "parent"
					Layout.fillWidth: true
				}
				//</workaround.puppet.CuteHMI.Modbus-1>
			}

			Label {
				text: qsTr("Delegate property")
			}

			SecondColumnLayout {
				LineEdit {
					backendValue: backendValues.delegateProperty
					Layout.fillWidth: true
					showExtendedFunctionButton: true
					showTranslateCheckBox: false
				}
			}

			Label {
				text: qsTr("Read-only")
			}

			SecondColumnLayout {
				CheckBox {
					backendValue: backendValues.readOnly
					implicitWidth: 180
				}
				ExpandingSpacer {
				}
			}

			Label {
				text: qsTr("Read-on-write")
			}

			SecondColumnLayout {
				CheckBox {
					backendValue: backendValues.readOnWrite
					implicitWidth: 180
				}
				ExpandingSpacer {
				}
			}

			Label {
				text: qsTr("Write mode")
			}

			SecondColumnLayout {
				ComboBox {
					model: ["WRITE_DELAYED", "WRITE_POSTPONED", "WRITE_IMMEDIATE", "WRITE_EXPLICIT"]
					backendValue: backendValues.writeMode
					Layout.fillWidth: true
					scope: "DiscreteInputController"
				}
			}

			Label {
				text: qsTr("Write delay")
			}

			SecondColumnLayout {
				SpinBox {
					backendValue: backendValues.writeDelay
					minimumValue: 0
					maximumValue: 1000000000
					Layout.preferredWidth: 80
				}
			}
		}
	}
}

//(c)C: Copyright © , . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
