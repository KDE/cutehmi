import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import CuteHMI.GUI 0.0
import CuteHMI.Symbols.HVAC 0.0

/**
  %Main component.
*/
Rectangle {
	anchors.fill: parent

	color: CuteApplication.theme.palette.background

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

				value: CuteApplication.theme.units.quadrat

				onValueChanged: CuteApplication.theme.units.quadrat = value
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
				}
			}
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
