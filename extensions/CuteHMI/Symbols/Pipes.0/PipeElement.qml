import QtQuick 2.0

import CuteHMI.GUI 0.0

/**
  Pipe element.
  */
Item {
	property real diameter: CuteApplication.theme.units.quadrat * 0.125

	property real thickness: diameter * 0.125

	property PipeColor color: PipeColor {}
}
