import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

ColumnLayout {
	property Service service

	RowLayout {
		Label {
			text: qsTr("%1 status:").arg(service.name)
		}

		Label {
			text: service.status
		}
	}

	Row {
		Layout.alignment: Qt.AlignRight

		spacing: 5

		Button {
			text: qsTr("Start")
			onClicked: service.start()
		}

		Button {
			text: qsTr("Stop")
			onClicked: service.stop()
		}
	}
}
