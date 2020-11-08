import QtQuick 2.0
import QtQuick.Controls 2.12

import CuteHMI 2.0

Item {

	Column {
		anchors.centerIn: parent

		spacing: 10

		Label {
			//! [Translation string]
			text: qsTr("Hello!")
			//! [Translation string]
			font.pointSize: 15
		}

		ComboBox {
			textRole: "text"
			valueRole: "value"
			model: [
				{ value: "en_US", text: "English" },
				{ value: "eo_001", text: "Esperanto" },
			]

			//! [Setting currentIndex]
			Component.onCompleted: currentIndex = indexOfValue(Internationalizer.uiLanguage)
			//! [Setting currentIndex]

			//! [Language activated]
			onActivated: Internationalizer.uiLanguage = model[index].value
			//! [Language activated]
		}
	}
}
