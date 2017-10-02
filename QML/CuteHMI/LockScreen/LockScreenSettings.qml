import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

Item {
    property alias changePasswordButton: changePasswordButton

    Frame {
        anchors.centerIn: parent
        padding: 20.0
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

            SpinBox {
                id: lockScreenTimeout
                from: 10
                to: 600
                value: 10
                stepSize: 10

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
            }
        }

    }
}
