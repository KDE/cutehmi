pragma Singleton

import QtQuick 2.0

/**
  %Palette.

  %Palette defines standard color sets to be used by CuteHMI items.
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

//(c)C: Copyright © 2018-2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
