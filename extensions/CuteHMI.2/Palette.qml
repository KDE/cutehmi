pragma Singleton

import QtQuick 2.0

/**
  %Palette.

  %Palette defines standard color sets to be used by %CuteHMI items.
  */
QtObject
{
	/**
	  Background color.
	  */
	property color background: "white"

	/**
	  Alarm color set.
	  */
	property ColorSet alarm: ColorSet {
		base: "#FF3300"
		fill: base
		tint: "#FF4B1D"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	/**
	  Warning color set.
	  */
	property ColorSet warning: ColorSet {
		base: "#FF9933"
		fill: base
		tint: "#FFA64D"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	/**
	  Active color set.
	  */
	property ColorSet active: ColorSet {
		base: "#66CC33"
		fill: base
		tint: "#CCF4CC"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	/**
	  Inactive color set.
	  */
	property ColorSet inactive: ColorSet {
		base: "#CECECE"
		fill: base
		tint: "#E3E3E3"
		shade: Qt.darker(base)
		foreground: "black"
		background: tint
		stroke: "black"
	}

	/**
	  Neutral color set is for items that do not distinguish between active and inactive states.
	  */
	property ColorSet neutral: ColorSet {
		base: "black"
		fill: "white"
		tint: Qt.lighter(base)
		shade: Qt.darker(base)
		foreground: "black"
		background: "white"
		stroke: "black"
	}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
