import qbs
import qbs.Utilities

import cutehmi

Project {
	name: "CuteHMI.Services.2"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Services"

		description: "Extension that helps creating services."

		files: [
			"README.md",
			"LICENSE.MIT",
			"LICENSE.LGPL3",
			"dev/CuteHMI.Services-1.workaround.Qml2Puppet.bug.txt",
			"dev/StandardStates.scxml",
			"include/cutehmi/services/Init.hpp",
			"include/cutehmi/services/PollingTimer.hpp",
			"include/cutehmi/services/Service.hpp",
			"include/cutehmi/services/ServiceListModel.hpp",
			"include/cutehmi/services/ServiceManager.hpp",
			"include/cutehmi/services/Serviceable.hpp",
			"include/cutehmi/services/internal/StateInterface.hpp",
			"include/cutehmi/services/internal/platform.hpp",
			"include/cutehmi/services/internal/common.hpp",
			"include/cutehmi/services/logging.hpp",
			"include/cutehmi/services/metadata.hpp",
			"src/cutehmi/services/Init.cpp",
			"src/cutehmi/services/PollingTimer.cpp",
			"src/cutehmi/services/Service.cpp",
			"src/cutehmi/services/ServiceListModel.cpp",
			"src/cutehmi/services/ServiceManager.cpp",
			"src/cutehmi/services/internal/QMLPlugin.cpp",
			"src/cutehmi/services/internal/QMLPlugin.hpp",
			"src/cutehmi/services/internal/StateInterface.cpp",
			"src/cutehmi/services/logging.cpp",
		]

		Depends { name: "Qt.core" }

		//<CuteHMI.Services-2.workaround target="Qt" cause="Qt5">
		Depends { name: "Qt.statemachine"; condition: Utilities.versionCompare(Qt.core.version, "6.0.0") >= 0 }
		//</CuteHMI.Services-2.workaround>

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'tests']

		Depends { name: "cutehmi.init" }

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Export {
			Depends { name: "Qt.core" }

			Depends { name: "Qt.statemachine"; condition: Utilities.versionCompare(Qt.core.version, "6.0.0") >= 0 }

			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
