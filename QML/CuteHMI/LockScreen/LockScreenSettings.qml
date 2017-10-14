import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

import CuteHMI.alpha.Controls 1.0

Item {
	id: root
	property url lockScreenUrl

	StackView {
		id: stackView
		anchors.fill: parent
		initialItem: Item {
			Frame {
				anchors.centerIn: parent
				padding: 20.0

				property alias changePasswordButton: changePasswordButton

				GridLayout {
					id: gridLayout
					rowSpacing: 40.0
					columnSpacing: 30.0
					columns: 2

					Label {
						text: qsTr("Ekran blokady: ")
						Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
					}

					Switch {
						id: lockScreenSwitch

						Settings {
							category: "LockScreen"
							property alias activated: lockScreenSwitch.checked
						}
					}

					Label {
						text: qsTr("Czas włączania blokady: ")
						Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
					}

					RealSpinBox {
						id: lockScreenTimeout
						from: 10
						to: 600
						value: 10
						stepSize: 10
						suffix: " s"

						Settings {
							category: "LockScreen"
							property alias timeout: lockScreenTimeout.value
						}
					}

					Label {
						text: qsTr("Zmiana hasła: ")
						Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
					}

					Button {
						id: changePasswordButton
						text: qsTr("zmień...")
						onClicked: stackView.push(changePasswordWizard)
					}
				}
			}
		}
	}

	Component {
		id: changePasswordWizard

		ChangePasswordWizard {
			onFinished: stackView.pop()
			lockScreenUrl: lockScreenUrl
		}
	}
}
