pragma Singleton

import QtQuick 2.0

QtObject
{
	property color text: foreground.text
	property color alarm: foreground.alarm
	property color warning: foreground.warning
	property color normal: foreground.normal
	property color disabled: foreground.disabled

	property QtObject foreground: QtObject {
		readonly property color text: "black"
		readonly property color alarm: "#FF3300"
		readonly property color warning: "#FF9933"
		readonly property color normal: "#66CC33"
		readonly property color disabled: "#CECECE"
	}

	property QtObject background: QtObject {
		readonly property color text: "white"
		readonly property color alarm: "#FF4B1D"
		readonly property color warning: "#FFA64D"
		readonly property color normal: "#CCF4CC"
		readonly property color disabled: "#E3E3E3"
	}

//	property color on: "#66CC33"
//	property color off: "#000000"

//	property color cold: "#0099FF"
//	property color optimal: "#66CC33"
//	property color hot: "#FF3300"	
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
