import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.14

import CuteHMI.Services 2.0
import CuteHMI.SharedDatabase 0.0
import CuteHMI.DataAcquisition 0.0

ColumnLayout {
	anchors.fill: parent

	BusyIndicator {
		anchors.centerIn: parent
		parent: Overlay.overlay
		running: schema.busy
	}

	Service {
		id: dbService

		name: "Database Service"

		Database {
			connectionName: "myConnection"
			type: "QPSQL"
//			type: "QSQLITE"
			host: "localhost"
			port: 5432
			name: "test"
			user: "postgres"
			password: "postgres"

//			threaded: false
//			onConnected: historyService.start()
		}

//		onStarted: historyService.start()
	}

	Schema {
		id: schema

		name: "my"

		connectionName: "myConnection"
	}

	ColumnLayout {
		Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

		Row {
			spacing: 5

			Label {
				text: dbService.name + ":"
			}

			Label {
				text: dbService.status
			}
		}

		Row {
			spacing: 5

			Label {
				text: historyService.name + ":"
			}

			Label {
				text: historyService.status
			}
		}

		Row {
			spacing: 5

			Label {
				text: recencyService.name + ":"
			}

			Label {
				text: recencyService.status
			}
		}

		Row {
			spacing: 5

			Label {
				text: eventService.name + ":"
			}

			Label {
				text: eventService.status
			}
		}

		Row {
			spacing: 5

			Button {
				text: qsTr("Start DB")
				onClicked: dbService.start()
			}

			Button {
				text: qsTr("Stop DB")
				onClicked: dbService.stop()
			}

		}

		Row {
			spacing: 5

			Button {
				text: qsTr("Start All")
				onClicked: {
					ServiceManager.start()
				}
			}

			Button {
				text: qsTr("Stop All")
				onClicked: {
					ServiceManager.stop()
				}
			}

			Button {
				text: qsTr("Start History")
				onClicked: historyService.start()
			}

			Button {
				text: qsTr("Stop History")
				onClicked: historyService.stop()
			}

			Button {
				text: qsTr("Start Recency")
				onClicked: recencyService.start()
			}

			Button {
				text: qsTr("Stop Recency")
				onClicked: recencyService.stop()
			}

			Button {
				text: qsTr("Start Event")
				onClicked: eventService.start()
			}

			Button {
				text: qsTr("Stop Event")
				onClicked: eventService.stop()
			}
		}

		Row {
			spacing: 5

			Button {
				text: qsTr("Create schema")
				onClicked: schema.create()
			}

			Button {
				text: qsTr("Drop schema")
				onClicked: schema.drop()
			}
		}

//		Tag {
//			id: tag

//			schema: schema

//			name: "testTag"
//		}

		Service {
			id: eventService

			name: "Event Service"

			EventWriter {
				schema: schema

				TagValue {
					name: "aa1.bool"
					value: dupaCheckbox.checked
				}

				TagValue {
					name: "fp5.aa"
					value: dupaSlider.intValue + 2
				}

				TagValue {
					name: "fp5.real"
					value: dupaSlider.value
				}

				TagValue {
					name: "fp6.real"
					value: dupaSlider.value + 0.1
				}
			}
		}

		Service {
			id: recencyService

			name: "Recency Service"

			RecencyWriter {
				schema: schema
//				interval: 10000

				TagValue {
					name: "aa1.bool"
					value: dupaCheckbox.checked
				}

				TagValue {
					name: "fp5.aa"
					value: dupaSlider.intValue + 2
				}

				TagValue {
					name: "fp5.bb"
					value: dupaSlider.intValue
				}

				TagValue {
					name: "fp5.real"
					value: dupaSlider.value
				}
			}
		}

		Service {
			id: historyService

			name: "History Service"

			HistoryWriter {
				id: history

				schema: schema
				interval: 250
				samples: 25

//				onStopped:  {
//					console.log("STTTTTTTTTTTTTTTTTOPPPPPPPPPPPPPPPEDDDDDDDD")
//				}

//				onStopped: dbService.stop()

//				Component.onCompleted: console.log(values)
//				values: [
				TagValue {
					name: "fp1.fill"
					property bool k: true
					value: k
				}

				TagValue {
					name: "fp2.fill"
					value: true
				}

				TagValue {
					name: "fp4.duspa"
					value: dupaSlider.intValue
				}

				TagValue {
					name: "fp5.aa"
					value: dupaSlider.intValue + 2
				}

				TagValue {
					name: "aa1.real"
					value: dupaSlider.value * 0.5 + 10
				}

				TagValue {
					name: "aa2.real"
					value: dupaSlider.value
				}

				TagValue {
					name: "aa1.bool"
					value: dupaCheckbox.checked
				}

				TagValue {
					name: "aa2.bool"
					value: dupaCheckbox.checked
				}

//				]
			}
		}

		RecencyModel {
			id: recencyModel

			schema: schema
		}

			Button {
				text: "Recency Update"
				onClicked: recencyModel.requestUpdate()
			}

			Button {
				text: "Push"
				onClicked: history.pushValues()
			}

			Button {
				text: "Validate schema test"
				onClicked: schema.validate()
			}

			Slider {
				id: dupaSlider
				from: 0
				to: 100
				property int intValue: value
			}

			CheckBox {
				id: dupaCheckbox
			}

		Row {
			spacing: 5

			Button {
				text: qsTr("Create tag")
				onClicked: tag.create()
			}

			Button {
				text: qsTr("Drop tag")
				onClicked: tag.drop()
			}
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
