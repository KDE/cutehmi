pragma Singleton

import QtQuick 2.0

/*!
  \qmltype Palette
  \inqmlmodule CuteHMI.Base
  \since CuteHMI.Base 1.0
  \brief Palette.

  Palette defines standard colors to be used with CuteHMI components.
  */
QtObject
{
	property color background: "white"

	property ColorSet alarm: ColorSet {
		base: "#FF3300"
		tint: "#FF4B1D"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	property ColorSet warning: ColorSet {
		base: "#FF9933"
		tint: "#FFA64D"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	property ColorSet active: ColorSet {
		base: "#66CC33"
		tint: "#CCF4CC"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	property ColorSet inactive: ColorSet {
		base: "#CECECE"
		tint: "#E3E3E3"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	/**
	  Neutral color set is for elements that do not distinguish between active and inactive states.
	  */
	property ColorSet neutral: ColorSet {
		base: "white"
		tint: Qt.lighter(base)
		shade: Qt.darker(base)
		foreground: "black"
		background: "white"
		stroke: "black"
	}

//	property color on: "#66CC33"
//	property color off: "#000000"

//	property color cold: "#0099FF"
//	property color optimal: "#66CC33"
//	property color hot: "#FF3300"	
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
