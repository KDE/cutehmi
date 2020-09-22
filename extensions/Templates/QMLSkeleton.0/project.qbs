import qbs

import cutehmi

Project {
	name: "Templates.QMLSkeleton.0"

	cutehmi.Extension {
		name: parent.name

		vendor: "The Secret Order of Templates"

		domain: "xn--cuthmi-5of.kde.org"

		friendlyName: "QML Skeleton"

		description: "QML extension skeleton."

		files: [
			"README.md",
			"LICENSE.MIT",
			"LICENSE.LGPL3",
			"View.qml",
		]

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.exclude: ['tests']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }
	}
}

//(c)ANYONE: Copyright © 2020, Anyone. All rights reserved.
//(c)ANYONE: This file is a part of CuteHMI.
//(c)ANYONE: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)ANYONE: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)ANYONE: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
