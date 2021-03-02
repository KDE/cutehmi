import QtQml.Models 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 3.0

ColumnLayout {
	id: root

	property string title: qsTr("Coil")

	property AbstractDevice device

	property Item delegate

	property alias controller: controller

	CoilController {
		id: controller

		device: root.device
		address: addressBox.value
		readOnWrite: readOnWriteBox.checked
		writeDelay: writeDelayBox.value
		writeMode: writeModeBox.value
		enabled: enabledBox.checked

		onValueUpdated: delegate.checked = value
	}

	Connections {
		target: delegate

		function onCheckedChanged() {
			controller.value = delegate.checked
		}
	}

	Label {
		text: root.title
	}

	GroupBox {
		GridLayout {
			columns: 2

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Address:")
			}

			SpinBox {
				id: addressBox

				from: 0
				to: 65536
				editable: true
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Write mode:")
			}

			ComboBox {
				id: writeModeBox

				textRole: "key"
				model: ListModel {
					ListElement {
						key: "Delayed"
						value: CoilController.WRITE_DELAYED
					}
					ListElement {
						key: "Postponed"
						value: CoilController.WRITE_POSTPONED
					}
					ListElement {
						key: "Immediate"
						value: CoilController.WRITE_IMMEDIATE
					}
					ListElement {
						key: "Explicit"
						value: CoilController.WRITE_EXPLICIT
					}
				}

				property int value: model.get(currentIndex).value

				onActivated: value = model.get(index).value
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Write delay:")
			}

			SpinBox {
				id: writeDelayBox

				enabled: controller.writeMode == CoilController.WRITE_DELAYED

				from: 0
				to: 1000
				stepSize: 100

				value: 500
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Read on write:")
			}

			CheckBox {
				id: readOnWriteBox

				checked: true
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Enabled:")
			}

			CheckBox {
				id: enabledBox

				checked: true
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
