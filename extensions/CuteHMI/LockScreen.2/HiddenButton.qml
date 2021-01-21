import QtQuick 2.7
import QtQuick.Controls 2.2

AbstractButton {
	id: root

	implicitWidth: 150
	implicitHeight: 150

	checkable: true

	contentItem: Text {
		text: root.text
		visible: (root.display !== AbstractButton.IconOnly) && root.down ? true : false
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		color: palette.buttonText
	}

	background: Rectangle {
		id: buttonBackground
		color: palette.button
		opacity: root.down ? 0.4 : 0.0
		radius: root.radius
	}

	property real radius: 0
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
