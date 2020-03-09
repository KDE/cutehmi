import QtQuick 2.0

/**
  Pipe connector.

  Pipe connector defines connection point of a pipe. If pipe connector has defined parent item, then coordinates are relative to the
  parent. They are also affected by parent transformations (such as rotation or scale). If parent item is not specified, then it is
  assumed that they are relative to Pipe object.
  */
QtObject {
	property real x: 0.0

	property real y: 0.0

	property Item parent

	function mapToPipe(pipe, other) {
		if (parent != undefined)
			return pipe.parent.mapFromItem(parent, x, y)
		else
			return Qt.point(x, y)
	}
}
