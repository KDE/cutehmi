import qbs 1.0
import qbs.Probes
import qbs.FileInfo
import qbs.Environment

Module {
	property bool found: libraryProbe.found && headerProbe.found

	property bool available: found && (qbs.targetOS.contains("windows") ? cutehmi.probes.libintl.available : true)

	property string libraryPath: libraryProbe.filePath

	property string includePath: headerProbe.path

	Probes.PathProbe {
		id: libraryProbe

        names: ["libpq"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: headerProbe

		names: ["libpq-fe"]
		nameSuffixes: [".h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
        pathSuffixes: ["postgresql"]
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.probes.libintl" }

	validate: {
		if (!cutehmi.probes.libintl.available)
			console.warn("Library 'libpq' may not be available, because its dependency 'libintl' may not be available.")
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
