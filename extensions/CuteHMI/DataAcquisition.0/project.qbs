import qbs

import cutehmi

Project {
	name: "CuteHMI.DataAcquisition.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Data Acquisition"

		description: "Data acquisition fundamental components."

		files: [
         "Console.qml",
		 "LICENSE.MIT",
		 "LICENSE.LGPL3",
		 "README.md",
         "include/cutehmi/dataacquisition/AbstractListModel.hpp",
         "include/cutehmi/dataacquisition/AbstractWriter.hpp",
         "include/cutehmi/dataacquisition/EventModel.hpp",
         "include/cutehmi/dataacquisition/EventWriter.hpp",
         "include/cutehmi/dataacquisition/Exception.hpp",
         "include/cutehmi/dataacquisition/HistoryModel.hpp",
         "include/cutehmi/dataacquisition/HistoryWriter.hpp",
         "include/cutehmi/dataacquisition/Init.hpp",
         "include/cutehmi/dataacquisition/RecencyModel.hpp",
         "include/cutehmi/dataacquisition/RecencyWriter.hpp",
         "include/cutehmi/dataacquisition/Schema.hpp",
         "include/cutehmi/dataacquisition/TagValue.hpp",
         "include/cutehmi/dataacquisition/internal/DbServiceableMixin.hpp",
         "include/cutehmi/dataacquisition/internal/EventCollective.hpp",
         "include/cutehmi/dataacquisition/internal/HistoryCollective.hpp",
         "include/cutehmi/dataacquisition/internal/ModelMixin.hpp",
         "include/cutehmi/dataacquisition/internal/RecencyCollective.hpp",
         "include/cutehmi/dataacquisition/internal/TableCollective.hpp",
         "include/cutehmi/dataacquisition/internal/TableNameTraits.hpp",
         "include/cutehmi/dataacquisition/internal/TableObject.hpp",
         "include/cutehmi/dataacquisition/internal/TagCache.hpp",
         "include/cutehmi/dataacquisition/internal/common.hpp",
         "include/cutehmi/dataacquisition/internal/platform.hpp",
         "include/cutehmi/dataacquisition/logging.hpp",
         "include/cutehmi/dataacquisition/metadata.hpp",
         "sql/postgres/create.sql",
         "sql/postgres/drop.sql",
         "sql/sqlite/create.sql",
         "sql/sqlite/drop.sql",
         "src/cutehmi/dataacquisition/AbstractListModel.cpp",
         "src/cutehmi/dataacquisition/AbstractWriter.cpp",
         "src/cutehmi/dataacquisition/EventModel.cpp",
         "src/cutehmi/dataacquisition/EventWriter.cpp",
         "src/cutehmi/dataacquisition/HistoryModel.cpp",
         "src/cutehmi/dataacquisition/HistoryWriter.cpp",
         "src/cutehmi/dataacquisition/Init.cpp",
         "src/cutehmi/dataacquisition/RecencyModel.cpp",
         "src/cutehmi/dataacquisition/RecencyWriter.cpp",
         "src/cutehmi/dataacquisition/Schema.cpp",
         "src/cutehmi/dataacquisition/TagValue.cpp",
         "src/cutehmi/dataacquisition/internal/EventCollective.cpp",
         "src/cutehmi/dataacquisition/internal/HistoryCollective.cpp",
         "src/cutehmi/dataacquisition/internal/QMLPlugin.cpp",
         "src/cutehmi/dataacquisition/internal/QMLPlugin.hpp",
         "src/cutehmi/dataacquisition/internal/RecencyCollective.cpp",
         "src/cutehmi/dataacquisition/internal/TableCollective.cpp",
         "src/cutehmi/dataacquisition/internal/TableObject.cpp",
         "src/cutehmi/dataacquisition/internal/TagCache.cpp",
         "src/cutehmi/dataacquisition/internal/helpers.hpp",
         "src/cutehmi/dataacquisition/logging.cpp",
     ]

		cutehmi.dirs.artifacts: true

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'puppet', 'tests']

		Depends { name: "cutehmi.init" }

		Depends { name: "cutehmi.qmldir" }
		cutehmi.qmldir.exclude: ["^designer/.*", "\.js$"]

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.skeleton.cpp" }
		cutehmi.skeleton.cpp.generateQMLPlugin: true

		Depends { name: "CuteHMI.SharedDatabase.0" }

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		Depends { name: "CuteHMI.Workarounds.Qt5Compatibility.0"; cpp.link: false }
		//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

		Export {
			Depends { name: "CuteHMI.SharedDatabase.0" }
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
