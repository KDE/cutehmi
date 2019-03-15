import qbs 1.0
import qbs.Probes
import qbs.FileInfo

/**
  Library for GPIO support.
  */
Module {
	property bool found: libgpiodProbe.found && libgpiodHeaderProbe.found

	property bool available: found

	property string libgpiodPath: libgpiodProbe.filePath

	property string includePath: libgpiodHeaderProbe.path

	Properties {
		condition: qbs.targetOS.contains("linux") && found
		cpp.dynamicLibraries: ["gpiod"]
	}

	Probes.PathProbe {
		id: libgpiodProbe

		names: ["libgpiod"]
		nameSuffixes: [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: libgpiodHeaderProbe

		names: ["gpiod.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
