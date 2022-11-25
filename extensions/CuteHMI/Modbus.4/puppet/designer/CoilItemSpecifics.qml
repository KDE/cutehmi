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
				text: qsTr("Controller")
			}

			SecondColumnLayout {
				//<workaround.puppet.CuteHMI.Modbus-1 target="QtCreator" cause="missing">
				// Using Label instead of
				//	placeholderText: backendValue.expression
				// Placeholder text is not visible. Hiding LineEdit by setting maximum width to 'actionIndicator.width'.
				LineEdit {
					id: controllerLineEdit

					backendValue: backendValues.controller
					Layout.maximumWidth: actionIndicator.width
					showExtendedFunctionButton: true
					showTranslateCheckBox: false
					readOnly: true
				}

				Label {
					text: controllerLineEdit.backendValue.expression
					Layout.fillWidth: true
				}
				//</workaround.puppet.CuteHMI.Modbus-1>
			}

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

					backendValue: backendValues.controller_device
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
					backendValue: backendValues.controller_address
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
					text: "(" + (backendValues.controller_address.value + 1) + ")"
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
					backendValue: backendValues.controller_readOnWrite
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
					backendValue: backendValues.controller_writeMode
					Layout.fillWidth: true
					scope: "CoilController"
				}
			}

			Label {
				text: qsTr("Write delay")
			}

			SecondColumnLayout {
				SpinBox {
					backendValue: backendValues.controller_writeDelay
					minimumValue: 0
					maximumValue: 1000000000
					Layout.preferredWidth: 80
				}
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
