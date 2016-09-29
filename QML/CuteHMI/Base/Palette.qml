pragma Singleton

import QtQuick 2.0

QtObject
{
	property color alert: "#FF3300"
	property color warning: "#FF9933"
	property color normal: "#66CC33"
	property color disabled: "#CECECE"

	property QtObject background: QtObject {
		property color alert: "#FF3300"
		property color warning: "#FF9933"
		property color normal: "#CCF4CC"
		property color disabled: "#E3E3E3"
	}

//	property color on: "#66CC33"
//	property color off: "#000000"

//	property color cold: "#0099FF"
//	property color optimal: "#66CC33"
//	property color hot: "#FF3300"
}
