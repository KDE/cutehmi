import QtQuick 2.0

import CuteHMI.GUI 0.0

/**
  %Element.

  This component should be used to implement color code aware items.
  */
Item {
	implicitWidth: units.quadrat
	implicitHeight: units.quadrat

	/**
	  Units used by the element.
	  */
	property Units units: CuteApplication.theme.units

	/**
	  %Palette. %Palette to be used by an element.
	  */
	property Palette palette: CuteApplication.theme.palette

	/**
	  This property defines current colors that should be used to draw element contents. By default, @a color properties are binded
	  to the respective properties of active @ref colorSet "color set". However, current color values may differ from those of
	  active color set, when color transitions take place.
	  */
	property ColorSet color: ColorSet {
		base: colorSet.base

		fill: colorSet.fill

		tint: colorSet.tint

		shade: colorSet.shade

		foreground: colorSet.foreground

		background: colorSet.background

		stroke: colorSet.stroke

		property color blank: palette.neutral.fill

		Behavior on base { ColorAnimation {} }
		Behavior on fill { ColorAnimation {} }
		Behavior on tint { ColorAnimation {} }
		Behavior on shade { ColorAnimation {} }
		Behavior on foreground { ColorAnimation {} }
		Behavior on background { ColorAnimation {} }
		Behavior on stroke { ColorAnimation {} }
		Behavior on blank { ColorAnimation {} }
	}

	/**
	  Active color set. Normally this is controlled by currentStateColorSet() function, which sets appropriate color
	  according to the state of @a active, @a warning and @a alarm properties. Neutral elements are binded to neutral color set.
	  */
	property ColorSet colorSet: neutral ? palette.neutral : currentStateColorSet()

	/**
	  Denotes if element is neutral (it does not distinguish between active, inactive, warning and alarm states).
	  */
	property bool neutral: false

	/**
	  Denotes if an item is in active state.
	  */
	property bool active: false

	/**
	  Denotes if an item is in warning state. Warning state should take precedence over @a active state.
	  */
	property bool warning: false

	/**
	  Denotes if an item is in alarm state. Alarm state should take precedence over @a warning and @a active states.
	  */
	property bool alarm: false

	/**
	  Pick color set based on active, warning and alarm property states. Alarm takes precedence before warning and warning takes
	  precedence over active state. For warning and alarm states this function dynamically alters the colors to carry visual
	  information more effectively and to provide accessibility to color blind people.

	  @return type:ColorSet appropriate color set.
	  */
	function currentStateColorSet() {
		return alarm ? (blinkTimer.blink ? alarmBlink : palette.alarm) :
			   warning ? (blinkTimer.blink ? warningBlink : palette.warning) :
			   active ? palette.active : palette.inactive
	}

	ColorSet {
		id: warningBlink

		base: Qt.lighter(palette.warning.base)
		fill: Qt.lighter(palette.warning.fill)
		tint: Qt.lighter(palette.warning.tint)
		shade: Qt.lighter(palette.warning.shade)
		foreground: Qt.lighter(palette.warning.foreground)
		background: Qt.lighter(palette.warning.background)
		stroke: Qt.lighter(palette.warning.stroke, 2.0)
	}

	ColorSet {
		id: alarmBlink

		base: Qt.lighter(palette.alarm.base)
		fill: palette.alarm.stroke
		tint: palette.alarm.shade
		shade: palette.alarm.tint
		foreground: palette.alarm.background
		background: palette.alarm.foreground
		stroke: palette.alarm.fill
	}

	Timer {
		id: blinkTimer

		interval: blink ? 250 : alarm ? 250 : 1500
		running: warning || alarm
		repeat: true

		property bool blink: false

		onTriggered: blink = !blink
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
