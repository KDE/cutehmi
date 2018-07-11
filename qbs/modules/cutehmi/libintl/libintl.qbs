import qbs 1.0
import qbs.Probes
import qbs.FileInfo

/**
  Library for native language support (part of gettext).
  */
Module {
	cpp.libraryPaths: FileInfo.cleanPath(libintlProbe.path)

	cpp.includePaths: FileInfo.cleanPath(libintlHeaderProbe.path)

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libintl-8"]
	}

	Properties {
        condition: qbs.targetOS.contains("linux") && found
		cpp.dynamicLibraries: ["intl"]
	}

	property bool found: libintlProbe.found && libintlHeaderProbe.found

	property bool available: found && cutehmi.libiconv.available

	property string libintlPath: libintlProbe.filePath

	property string includePath: libintlHeaderProbe.path

	Probes.PathProbe {
		id: libintlProbe

        names: qbs.targetOS.contains("windows") ? ["libintl-8"] : ["libintl"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: libintlHeaderProbe

		names: ["libintl.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.libiconv" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
