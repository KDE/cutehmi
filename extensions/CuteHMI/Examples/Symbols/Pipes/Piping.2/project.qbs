import qbs

import cutehmi

Project {
	name: "CuteHMI.Examples.Symbols.Pipes.Piping.2"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Extension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Piping Example"

		description: "Piping example using CuteHMI.Symbols.Pipes.1 extension."

		files: [
			"LICENSE.MIT",
			"LICENSE.LGPL3",
			"View.qml",
			"README.md",
		]

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.useDoxyqml: true

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.view.4" }

		Depends { name: "CuteHMI.Symbols.Pipes.1" }
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
