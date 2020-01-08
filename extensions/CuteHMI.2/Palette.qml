pragma Singleton

import QtQuick 2.0

/**
  %Palette.

  %Palette defines standard color sets to be used by various user interface items.
  */
QtObject
{
	/**
	  Default theme.
	  */
	readonly property Theme defaultTheme: Theme {}

	/**
	  Current theme
	  */
	property Theme theme: defaultTheme

	/**
	  Background color.
	  */
	property color background: theme.background

	/**
	  Alarm color set.
	  */
	property ColorSet alarm: theme.alarm

	/**
	  Warning color set.
	  */
	property ColorSet warning: theme.warning

	/**
	  Active color set.
	  */
	property ColorSet active: theme.active

	/**
	  Inactive color set.
	  */
	property ColorSet inactive: theme.inactive

	/**
	  Neutral color set is for items that do not distinguish between active and inactive states.
	  */
	property ColorSet neutral: theme.neutral

	// Prevent warnings about accessing properties of null. This often happens with custom Themes as they are destroyed before Palette component.
	onThemeChanged: if (theme === null) theme = defaultTheme
}

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
