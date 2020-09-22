import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import CuteHMI.GUI 1.0
import CuteHMI.Symbols.HVAC 1.0

/**
  %View component.
*/
Rectangle {
	anchors.fill: parent

	color: Theme.palette.background

	ColumnLayout {
		anchors.fill: parent
		anchors.margins: 10

		spacing: 20

		RowLayout {
			Label {
				text: qsTr("Size:")
			}

			Slider {
				from: 10
				to: 240

				value: Theme.units.quadrat

				onValueChanged: Theme.units.quadrat = value
			}
		}

		Flickable {
			Layout.fillHeight: true
			Layout.fillWidth: true

			ScrollBar.vertical: ScrollBar {}
			ScrollBar.horizontal: ScrollBar {}

			contentWidth: row.width
			contentHeight: row.height

			Row {
				id: row

				GridLayout {
					rows: 3
					flow: GridLayout.TopToBottom

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Air filter")
					}

					AirFilter {
						id: filter

						Layout.alignment: Qt.AlignCenter
					}

					AirFilterSettings {
						Layout.alignment: Qt.AlignTop

						filter: filter
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Basic cooler")
					}

					BasicCooler {
						id: basicCooler

						Layout.alignment: Qt.AlignCenter
					}

					ElementSettings {
						Layout.alignment: Qt.AlignTop

						element: basicCooler
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Basic discrete instrument")
					}

					BasicDiscreteInstrument {
						id: basicDiscreteInstrument

						Layout.alignment: Qt.AlignCenter
					}

					BasicDiscreteInstrumentSettings {
						Layout.alignment: Qt.AlignTop

						instrument: basicDiscreteInstrument
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Basic heater")
					}

					BasicHeater {
						id: basicHeater

						Layout.alignment: Qt.AlignCenter
					}

					ElementSettings {
						Layout.alignment: Qt.AlignTop

						element: basicHeater
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Blade damper")
					}

					BladeDamper {
						id: bladeDamper

						Layout.alignment: Qt.AlignCenter
					}

					BladeDamperSettings {
						Layout.alignment: Qt.AlignTop

						damper: bladeDamper
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Centrifugal fan")
					}

					CentrifugalFan {
						id: centrifugalFan

						Layout.alignment: Qt.AlignCenter
					}

					CentrifugalFanSettings {
						Layout.alignment: Qt.AlignTop

						fan: centrifugalFan
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Cooler")
					}

					Cooler {
						id: cooler

						Layout.alignment: Qt.AlignCenter
					}

					ElementSettings {
						Layout.alignment: Qt.AlignTop

						element: cooler
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Heater")
					}

					Heater {
						id: heater

						Layout.alignment: Qt.AlignCenter
					}

					ElementSettings {
						Layout.alignment: Qt.AlignTop

						element: heater
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Heat exchanger")
					}

					HeatExchanger {
						id: heatExchanger

						Layout.alignment: Qt.AlignCenter
					}

					ElementSettings {
						Layout.alignment: Qt.AlignTop

						element: heatExchanger
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Heat recovery wheel")
					}

					HeatRecoveryWheel {
						id: wheel

						Layout.alignment: Qt.AlignCenter
					}

					HeatRecoveryWheelSettings {
						Layout.alignment: Qt.AlignTop

						wheel: wheel
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Motor actuator")
					}

					MotorActuator {
						id: motorActuator

						Layout.alignment: Qt.AlignCenter
					}

					MotorActuatorSettings {
						Layout.alignment: Qt.AlignTop

						actuator: motorActuator
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Pump")
					}

					Pump {
						id: pump

						Layout.alignment: Qt.AlignCenter
					}

					PumpSettings {
						Layout.alignment: Qt.AlignTop

						pump: pump
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Tank")
					}

					Tank {
						id: tank

						Layout.alignment: Qt.AlignCenter
					}

					TankSettings {
						Layout.alignment: Qt.AlignTop

						tank: tank
					}

					Label {
						Layout.alignment: Qt.AlignCenter

						text: qsTr("Valve")
					}

					Valve {
						id: valve

						Layout.alignment: Qt.AlignCenter
					}

					ValveSettings {
						Layout.alignment: Qt.AlignTop

						valve: valve
					}
				}
			}
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
