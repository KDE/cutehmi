import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import CuteHMI.GUI 1.0
import CuteHMI.Symbols.Pipes 1.0

/**
  %Main component.
*/
Rectangle {
	id: root

	anchors.fill: parent

	color: Theme.palette.background

	Pipe {
		from: PipeConnector {
			x: 20
			y: 20
		}

		to: PipeConnector {
			x: 200
			y: 20
		}
	}

	PipeConnector {
		id: verticalA

		x: 300
		y: 20
	}

	PipeConnector {
		id: verticalB
		x: 300
		y: 200
	}

	Pipe {
		from: verticalA
		to: verticalB
	}

	//! [Red rectangle]
	Rectangle {
		id: red

		x: 400
		y: 20

		width: 40
		height: 40
		color: "red"
		border.width: 1

		//! [Red rectangle outlet property]
		property PipeConnector outlet: PipeConnector {
			x: 40
			y: 20
			parent: red
		}
		//! [Red rectangle outlet property]
	}
	//! [Red rectangle]

	Rectangle {
		id: blue

		x: 600
		y: 20

		width: 40
		height: 40
		color: "blue"
		border.width: 1

		property PipeConnector inlet: PipeConnector {
			x: 0
			y: 20
			parent: blue
		}
	}

	//! [Red-blue pipe]
	Pipe {
		from: red.outlet
		to: blue.inlet

		color.interior: ["red", "blue"]
	}
	//! [Red-blue pipe]

	Rectangle {
		id: green

		x: 700
		y: 20

		width: 40
		height: 40
		color: "green"
		border.width: 1

		rotation: 90

		property PipeConnector outlet: PipeConnector {
			x: 40
			y: 20
			parent: green
		}
	}

	Rectangle {
		id: orange

		x: 700
		y: 200

		width: 40
		height: 40
		color: "orange"
		border.width: 1

		rotation: 90

		property PipeConnector inlet: PipeConnector {
			x: 0
			y: 20
			parent: orange
		}
	}

	Pipe {
		from: green.outlet
		to: orange.inlet

		color.interior: ["green", "orange"]
	}

	// Pipe elments example
	Tee {
		id: tee

		x: 100
		y: 300

		color.interior: "yellow"
	}

	Tee {
		id: teeFlip

		x: 200
		y: 300

		rotation: 180

		color.interior: "yellow"
	}

	Elbow {
		id: elbow

		x: 300
		y: 300

		color.interior: "yellow"
	}

	Elbow {
		id: elbow90

		x: 300
		y: 400
		rotation: 90

		color.interior: "yellow"
	}

	Elbow {
		id: elbow180

		x: 100
		y: 400
		rotation: 180

		color.interior: "yellow"
	}

	PipeEnd {
		id: leftEnd

		x: 20
		y: 300

		color.interior: "yellow"
	}

	PipeEnd {
		id: topEnd

		x: 200
		y: 250
		rotation: 90

		color.interior: "yellow"
	}

	Pipe {
		from: leftEnd.connector.sideB
		to: tee.connector.sideA

		color.interior: "orange"
	}

	Pipe {
		from: tee.connector.sideB
		to: teeFlip.connector.sideB

		color.interior: "orange"
	}

	Pipe {
		from: teeFlip.connector.sideA
		to: elbow.connector.sideA

		color.interior: "orange"
	}

	Pipe {
		from: elbow.connector.sideB
		to: elbow90.connector.sideA

		color.interior: "orange"
	}

	Pipe {
		from: elbow90.connector.sideB
		to: elbow180.connector.sideA

		color.interior: "orange"
	}

	Pipe {
		from: elbow180.connector.sideB
		to: tee.connector.middle

		color.interior: "orange"
	}

	Pipe {
		from: teeFlip.connector.middle
		to: topEnd.connector.sideB

		color.interior: "orange"
	}

	Tee {
		id: tee_2

		x: 400
		y: 300

		color.interior: "pink"
	}

	Tee {
		id: teeFlip_2

		x: 500
		y: 300

		rotation: 180

		color.interior: "pink"
	}

	Elbow {
		id: elbow_2

		x: 600
		y: 300

		color.interior: "pink"
	}

	Elbow {
		id: elbow90_2

		x: 600
		y: 400
		rotation: 90

		color.interior: "pink"
	}

	Elbow {
		id: elbow180_2

		x: 400
		y: 400
		rotation: 180

		color.interior: "pink"
	}

	PipeEnd {
		id: leftEnd_2

		x: 320
		y: 300

		color.interior: "pink"
	}

	PipeEnd {
		id: topEnd_2

		x: 500
		y: 250
		rotation: 90

		color.interior: "pink"
	}

	Cap {
		id: topCap_2

		x: 500
		y: 200

		color.interior: "pink"
		rotation: -90
	}

	Pipe {
		from: leftEnd_2.connector
		to: tee_2.connector

		color.interior: "violet"
	}

	Pipe {
		from: tee_2.connector
		to: teeFlip_2.connector

		color.interior: "violet"
	}

	Pipe {
		from: teeFlip_2.connector
		to: elbow_2.connector

		color.interior: "violet"
	}

	Pipe {
		from: elbow_2.connector
		to: elbow90_2.connector

		color.interior: "violet"
	}

	Pipe {
		from: elbow90_2.connector
		to: elbow180_2.connector

		color.interior: "violet"
	}

	Pipe {
		from: elbow180_2.connector
		to: tee_2.connector

		color.interior: "violet"
	}

	Pipe {
		from: teeFlip_2.connector
		to: topEnd_2.connector

		color.interior: "violet"
	}

	Pipe {
		from: topEnd_2.connector
		to: topCap_2.connector

		color.interior: "violet"
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
