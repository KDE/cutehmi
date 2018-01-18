import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import CuteHMI.App 1.0
import CuteHMI.LockScreen 1.0
import CuteHMI.alpha.Controls 1.0

/**
  @todo Set implicit width and height.

  @todo Try to use Item as lockScreenComponent property (change name to lockScreenItem in such case).

  @todo Try to use default property for lockScreenX property.

  @todo Fix image fit.
  */
Item {
	id: root

	property alias lockScreenComponent: wizard.lockScreenComponent

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
				text: qsTr("Ekran blokady:")
				Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
			}

			Switch {
				id: lockScreenSwitch
				checked: Settings.activated
				onCheckedChanged: Settings.activated = checked
			}

			Label {
				text: qsTr("Czas włączania blokady: ")
				Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
			}

			RealSpinBox {
				id: lockScreenTimeout
				from: 10
				to: 600
				stepSize: 10
				suffix: " s"
				value: Settings.timeout
				onValueChanged: Settings.timeout = value
			}

			Label {
				text: qsTr("Zmiana hasła: ")
				Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
			}

			Button {
				id: changePasswordButton
				text: qsTr("zmień...")
				onClicked: wizardPopup.open()
			}
		}
	}

	Popup {
		id: wizardPopup

		x: 10
		y: 10
		width: parent.width - 2 * x
		height: parent.height - 2 * y
		closePolicy: Popup.NoAutoClose
		modal: true

		ChangePasswordWizard {
			id: wizard

			anchors.fill: parent
			lockScreenComponent: root.lockScreenComponent
			onFinished: {
				wizardPopup.close()
			}
		}
	}
}
