import qbs 1.0
import qbs.Probes
import qbs.FileInfo
import qbs.Environment

Module {
	property bool found: libpqProbe.found && libpq_feHeaderProbe.found

    property bool available: found && (qbs.targetOS.contains("windows") ? cutehmi.libintl.available : true)

	property string libpqPath: libpqProbe.filePath

	property string includePath: libpq_feHeaderProbe.path

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libpq"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["pq"]
	}

	Probes.PathProbe {
		id: libpqProbe

        names: ["libpq"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		searchPaths: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: libpq_feHeaderProbe

		names: ["libpq-fe"]
		nameSuffixes: [".h"]
		searchPaths: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
        pathSuffixes: ["postgresql"]
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.libintl" }
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
