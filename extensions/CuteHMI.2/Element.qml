import QtQuick 2.0

//<CuteHMI-3.workaround target="Qt" cause="QTBUG-34418">
// Palette is a singleton.
// Singletons require explicit import to load qmldir file.
import "."
//</CuteHMI-3.workaround>

/**
  %Element.

  This component should be used to implement color code aware items.
  */
Item {
    implicitWidth: 40.0
    implicitHeight: 40.0

	/**
	  %Palette. %Palette to be used with an element.
	  */
	property Palette palette: Palette

	/**
	  Active color set. Normally this is controlled by currentStateColorSet() function, which sets appropriate color
	  according to the state of @a active, @a warning and @a alarm properties.
	  */
	property ColorSet colorSet: currentStateColorSet()

	/**
	  Base color. Base color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color baseColor: colorSet.base

	/**
	  Fill color. Fill color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color fillColor: colorSet.fill

	/**
	  Tint color. Tint color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color tintColor: colorSet.tint

	/**
	  Shade color. Shade color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color shadeColor: colorSet.shade

	/**
	  Foreground color. Foreground color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color foregroundColor: colorSet.foreground

	/**
	  Background color. Background color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color backgroundColor: colorSet.background

	/**
	  Stroke color. Stroke color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color strokeColor: colorSet.stroke

	/**
	  Blank color. Blank color that should be used by an item to draw its contents.
	  Refer to ColorSet documentation to see how to use color sets.
	  */
	property color blankColor: palette.neutral.fill

	/**
	  Line width. Line width that should be used by an item to draw its contents.
	  */
	property real lineWidth: 2.0

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
	  @return appropriate color set.
	  */
	function currentStateColorSet() {
		return alarm ? (blinkTimer.blink ? alarmBlink : palette.alarm) :
			   warning ? (blinkTimer.blink ? warningBlink : palette.warning) :
			   active ? palette.active : palette.inactive
	}

	Behavior on baseColor { ColorAnimation {} }
	Behavior on fillColor { ColorAnimation {} }
	Behavior on tintColor { ColorAnimation {} }
	Behavior on shadeColor { ColorAnimation {} }
	Behavior on foregroundColor { ColorAnimation {} }
	Behavior on backgroundColor { ColorAnimation {} }
	Behavior on strokeColor { ColorAnimation {} }

	ColorSet {
		id: warningBlink

		base: Qt.lighter(palette.warning.base)
		fill: Qt.lighter(palette.warning.fill)
		tint: Qt.lighter(palette.warning.tint)
		shade: Qt.lighter(palette.warning.shade)
		foreground: Qt.lighter(palette.warning.foreground)
		background: Qt.lighter(palette.warning.background)
		stroke: palette.warning.stroke
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

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
