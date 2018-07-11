import qbs 1.0
import qbs.Probes
import qbs.FileInfo
import qbs.Environment

Module {
	cpp.libraryPaths: FileInfo.cleanPath(libpqProbe.path)

	cpp.includePaths: FileInfo.cleanPath(libpq_feHeaderProbe.path)

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libpq"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["pq"]
	}

	property bool found: libpqProbe.found && libpq_feHeaderProbe.found

    property bool available: found && (qbs.targetOS.contains("windows") ? cutehmi.libintl.available : true)

	property string libpqPath: libpqProbe.filePath

	property string includePath: libpq_feHeaderProbe.path

	Probes.PathProbe {
		id: libpqProbe

        names: ["libpq"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: libpq_feHeaderProbe

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

	Depends { name: "cutehmi.libintl" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
