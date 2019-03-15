import QtQuick 2.0

/**
  Color set defines standard colors to be used by CuteHMI components.

  %CuteHMI components are using color codes to signal
  specific states of an equipment, such as "active", warning", "alarm", "inactive". To improve a visual appearance of
  a component a set of adjacent colors is provided to represent a state of the component.
  */
QtObject {
	/**
	  Base color of a set. It can be used to display single-color elements over the Palette's main background (such as text).
	  As such it should be contrasting with Palette's background.
	  */
	property color base

	/**
	  Fill color. As name suggests it can be used by components to fill their interiors. Fill color works together with stroke color.
	  Component must have a stroke contour if it uses fill color to fill its interior.
	  Either a stroke color or a fill color should be a variation of base color in order to make color set meaningful.
	  */
	property color fill

	/**
	  A lighter variation of fill color. It can be used to draw details of a component.
	  */
	property color tint

	/**
	  A darker variation of fill color. It can be used to draw details of a component.
	  */
	property color shade

	/**
	  Background color. Some components may want to display a text or symbols over them. Such components shall use
	  background color to create uniform background and a contrasting foreground color to display text/symbols. Foreground
	  and background colors work in pairs; in one theme background color is a dull variation of base color, while
	  foreground color remains the same across color sets, but the other theme may choose to make foreground color
	  a variation of base color and to keep background the same.
	  */
	property color background

	/**
	  Foreground color. Some components may want to display a text or symbols over them. Such components shall use
	  background color to create uniform background and a contrasting foreground color to display text/symbols. Foreground
	  and background colors work in pairs; in one theme background color is a dull variation of base color, while
	  foreground color remains the same across color sets, but the other theme may choose to make foreground color
	  a variation of base color and keep background the same across multiple sets.
	  */
	property color foreground

	/**
	  Strokes. A color of contours. Stroke color should be contrasting with Palette's main background. Stroke color works together
	  with fill color. Component must have a stroke contour if it uses fill color to fill its interior.
	  Either a stroke color or a fill color should be a variation of base color in order to make color set meaningful.
	  */
	property color stroke
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
