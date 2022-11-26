import qbs

import cutehmi

Project {
	name: "CuteHMI.SharedDatabase.1"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Shared Database"

		description: "Shared database connection provider."

		files: [
			"CHANGES.md",
			"Console.qml",
			"LICENSE.MIT",
			"LICENSE.LGPL3",
			"README.md",
			"include/cutehmi/shareddatabase/DataObject.hpp",
			"include/cutehmi/shareddatabase/Database.hpp",
			"include/cutehmi/shareddatabase/DatabaseWorker.hpp",
			"include/cutehmi/shareddatabase/PostgresMaintenance.hpp",
			"include/cutehmi/shareddatabase/internal/DatabaseConfig.hpp",
			"include/cutehmi/shareddatabase/internal/DatabaseConnectionHandler.hpp",
			"include/cutehmi/shareddatabase/internal/DatabaseThread.hpp",
			"include/cutehmi/shareddatabase/internal/common.hpp",
			"include/cutehmi/shareddatabase/internal/platform.hpp",
			"include/cutehmi/shareddatabase/logging.hpp",
			"include/cutehmi/shareddatabase/metadata.hpp",
			"src/cutehmi/shareddatabase/DataObject.cpp",
			"src/cutehmi/shareddatabase/Database.cpp",
			"src/cutehmi/shareddatabase/DatabaseWorker.cpp",
			"src/cutehmi/shareddatabase/PostgresMaintenance.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseConfig.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseConnectionHandler.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseDictionary.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseDictionary.hpp",
			"src/cutehmi/shareddatabase/internal/DatabaseThread.cpp",
			"src/cutehmi/shareddatabase/internal/QMLPlugin.cpp",
			"src/cutehmi/shareddatabase/internal/QMLPlugin.hpp",
			"src/cutehmi/shareddatabase/logging.cpp",
		]

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'puppet', 'tests']

		Depends { name: "cutehmi.qmldir" }
		cutehmi.qmldir.exclude: ["^designer/.*", "\.js$"]

		Depends { name: "cutehmi.qmltyperegistrar" }

		Depends { name: "cutehmi.skeleton.cpp" }
		cutehmi.skeleton.cpp.generateQMLPlugin: true

		Depends { name: "cutehmi.probes.libpq" }	// Using probe just to print some debug output. It is not required to link against client library.

		Depends { name: "Qt.sql" }

		Depends { name: "CuteHMI.Services.3" }

		Export {
			Depends { name: "Qt.sql" }

			Depends { name: "CuteHMI.Services.3" }
		}
	}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
