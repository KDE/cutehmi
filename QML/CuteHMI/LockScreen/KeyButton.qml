import QtQuick 2.7
import QtQuick.Controls 2.2

AbstractButton {
	id: root
	implicitWidth: 150
	implicitHeight: 150
	down: inverted ^ pressed

	background: Rectangle {
		id: buttonBackground
		color: "white"
		opacity: root.down ? 0.4 : 0.0
		radius: root.radius
	}

	property string value: '0'
	property alias radius: buttonBackground.radius
	property bool inverted: false

	signal valueTriggered(string value)

	Connections {
		onClicked: valueTriggered(value)
	}
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
