import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

import CuteHMI.Modbus 2.0

Control {
	padding: 20
	contentItem: ColumnLayout {
		spacing: 10

		RowLayout {
			Layout.alignment: Qt.AlignLeft

			Label {
				text: qsTr("Device type:")
			}

			ComboBox {
				textRole: "name"

				model: ListModel {
					ListElement { name: "DummyClient"; source: "DummyClientComposite.qml"}
				}

				onActivated: loader.source = model.get(currentIndex).source
			}
		}

		Loader {
			id: loader

			source: "DummyClientComposite.qml"
		}
	}

	property alias source: loader.source
}
