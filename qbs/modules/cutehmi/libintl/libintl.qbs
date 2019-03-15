import qbs 1.0
import qbs.Probes
import qbs.FileInfo

/**
  Library for native language support (part of gettext).
  */
Module {
	property bool found: libintlProbe.found && libintlHeaderProbe.found

	property bool available: found && cutehmi.libiconv.available

	property string libintlPath: libintlProbe.filePath

	property string includePath: libintlHeaderProbe.path

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libintl-8"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux") && found
		cpp.dynamicLibraries: ["intl"]
	}

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
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
