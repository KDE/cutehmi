# Graphical User Interface

This module provides foundation for GUI applications.

Class CuteHMI.GUI.CuteApplication provides idle measurment to frontend tools and projects.

CuteHMI.GUI.Palette, CuteHMI.GUI.Fonts and CuteHMI.GUI.ColorSet help provide consistent color codes accross projects.

CuteHMI.GUI.Theme singleton groups above components.

CuteHMI.GUI.Element component should be used to create color code aware items.

CuteHMI.GUI.NumberDisplay provides convenient display.

## Changes

Compared to previous major version, following changes have been made.

CuteHMI.GUI.CuteApplication has no `theme` and `defaultTheme` properties. Instead one should use CuteHMI.GUI.Theme, which is now a
singleton on its own.
