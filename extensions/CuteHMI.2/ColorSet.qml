import QtQuick 2.0

/**
  Color set defines standard colors to be used by CuteHMI components.

  CuteHMI components are using color codes to signal
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

//(c)C: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
