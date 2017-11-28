import QtQuick 2.0

/**
  Color set defines standard colors to be used by CuteHMI components. CuteHMI components are using color codes to signal
  specific states of an equipment, such as "normal", warning", "alarm", "disabled". To improve a visual appearance of
  a component a set of adjacent colors is provided to represent a state of the component.
  */
QtObject {
	/**
	  Base color of a set. It can be used by controls as a fill color, but it can be also used to draw a text over the
	  Palette's main background. As such it should be contrasting with Palette's background.
	  */
	property color base

	/**
	  A lighter variation of base color. It can be used to draw details of a component.
	  */
	property color tint

	/**
	  A darker variation of base color. It can be used to draw details of a component.
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
	  a variation of base color and to keep background the same.
	  */
	property color foreground

	/**
	  Strokes. A color of contours. Stroke color should be contrasting with Palette's main background. It is not required
	  for a stroke color to be a variation of base color, but themes may do so. Stroke color can be the same as foreground
	  color.
	  */
	property color stroke
}
