import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQml.Models 2.11

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

ColumnLayout {

	Component.onCompleted: ServiceManager.start()

	Service {
		id: clientService

		name: "Dummy"

		DummyClient {
			id: client

			pollingTimer.interval: 2000
			pollingTimer.subtimer.interval: 1000
		}
	}

	RowLayout {
		Layout.alignment: Qt.AlignCenter

		spacing: 40

		ColumnLayout {
			spacing: 40
			Layout.alignment: Qt.AlignTop

			ServiceControl {
				service: clientService
			}

			DeviceControl {
				device: client
				configurationItem: DummyClientConfiguration {
					client: client
				}
			}
		}

		ColumnLayout {
			spacing: 40

			RowLayout {
				HoldingRegisterControl {
					id: spinBoxControl

					title: qsTr("Holding register spin box")

					delegate: spinBox
					device: client

					RowLayout {
						Layout.alignment: Qt.AlignRight

						SpinBox {
							id: spinBox

							from: -32767
							to: 65535
							editable: true

							BusyIndicator {
								anchors.centerIn: parent
								running: spinBoxControl.controller.busy
							}
						}

						RoundButton {
							text: "\u2713"

							onClicked: spinBoxControl.controller.writeValue()
						}
					}
				}

				HoldingRegisterControl {
					title: qsTr("Holding register text field")

					delegate: textFiled
					device: client

					TextField {
						id: textFiled

						Layout.alignment: Qt.AlignRight

						text: Number(value).toLocaleString(locale, 'f', 3)
						validator: DoubleValidator {
							decimals: 3
						}

						property real value

						onAccepted: value = Number.fromLocaleString(locale, text)

						BusyIndicator {
							anchors.centerIn: parent
							running: parent.parent.controller.busy
						}
					}
				}

			}

			RowLayout {
				CoilControl {
					id: checkBoxControl

					title: qsTr("Coil check box")

					delegate: checkBox
					device: client

					RowLayout {
						Layout.alignment: Qt.AlignRight

						CheckBox {
							id: checkBox

							BusyIndicator {
								anchors.centerIn: parent
								running: checkBoxControl.controller.busy
							}
						}

						RoundButton {
							text: "\u2713"

							onClicked: checkBoxControl.controller.writeValue()
						}
					}
				}

				CoilControl {
					id: switchControl

					title: qsTr("Coil switch")

					delegate: switchItem
					device: client

					RowLayout {
						Layout.alignment: Qt.AlignRight

						Switch {
							id: switchItem

							BusyIndicator {
								anchors.centerIn: parent
								running: switchControl.controller.busy
							}
						}

						RoundButton {
							text: "\u2713"

							onClicked: switchControl.controller.writeValue()
						}
					}
				}
			}
		}
	}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
