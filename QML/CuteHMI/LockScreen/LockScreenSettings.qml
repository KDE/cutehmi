import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

Item {
    GridLayout {
        id: gridLayout
        anchors.centerIn: parent
        rowSpacing: 40.0
        columnSpacing: 30.0
        columns: 2


        Label {
            text: qsTr("Ekran blokady: ")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        }

        Switch {
            id: lockScreenSwitch
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

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
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

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
            text: qsTr("zmień...")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }

}
