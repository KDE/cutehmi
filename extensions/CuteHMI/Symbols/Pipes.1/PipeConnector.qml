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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
