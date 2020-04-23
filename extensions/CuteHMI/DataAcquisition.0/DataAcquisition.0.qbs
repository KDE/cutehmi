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
         "LICENSE",
         "README.md",
         "include/cutehmi/dataacquisition/AbstractWriter.hpp",
         "include/cutehmi/dataacquisition/DataModel.hpp",
         "include/cutehmi/dataacquisition/DataObject.hpp",
         "include/cutehmi/dataacquisition/EventWriter.hpp",
         "include/cutehmi/dataacquisition/Exception.hpp",
         "include/cutehmi/dataacquisition/HistoryWriter.hpp",
         "include/cutehmi/dataacquisition/RecencyWriter.hpp",
         "include/cutehmi/dataacquisition/Schema.hpp",
         "include/cutehmi/dataacquisition/TagValue.hpp",
         "include/cutehmi/dataacquisition/internal/EventCollective.hpp",
         "include/cutehmi/dataacquisition/internal/EventTable.hpp",
         "include/cutehmi/dataacquisition/internal/HistoryCollective.hpp",
         "include/cutehmi/dataacquisition/internal/HistoryTable.hpp",
         "include/cutehmi/dataacquisition/internal/RecencyCollective.hpp",
         "include/cutehmi/dataacquisition/internal/RecencyTable.hpp",
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
         "src/cutehmi/dataacquisition/AbstractWriter.cpp",
         "src/cutehmi/dataacquisition/DataModel.cpp",
         "src/cutehmi/dataacquisition/DataObject.cpp",
         "src/cutehmi/dataacquisition/EventWriter.cpp",
         "src/cutehmi/dataacquisition/HistoryWriter.cpp",
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
         "src/cutehmi/dataacquisition/logging.cpp",
     ]

		FileTagger {
			patterns: ["*.sql"]
			fileTags: ["sql"]
		}

		Group {
			name: "SQL"
			fileTagsFilter: ["sql"]
			qbs.install: true
			qbs.installSourceBase: installSourceBase
			qbs.installDir: dedicatedInstallSubdir
		}

		cutehmi.dirs.artifacts: true

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'puppet', 'tests']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }
		cutehmi.qmldir.exclude: ["^designer/.*", "\.js$"]

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.skeleton.cpp" }
		cutehmi.skeleton.cpp.generateQMLPlugin: true

		Depends { name: "CuteHMI.SharedDatabase.0" }

		Export {
			Depends { name: "CuteHMI.SharedDatabase.0" }
		}
	}
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
