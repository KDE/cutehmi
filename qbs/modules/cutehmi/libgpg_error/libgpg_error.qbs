import qbs 1.0
import qbs.Probes
import qbs.FileInfo

Module {
	cpp.libraryPaths: FileInfo.cleanPath(libgpg_errorProbe.path)

	cpp.includePaths: FileInfo.cleanPath(gpg_errorHeaderProbe.path)

	property bool found: libgpg_errorProbe.found && gpg_errorHeaderProbe.found

	property bool available: found

	property string libgpg_errorPath: libgpg_errorProbe.filePath

	property string includePath: gpg_errorHeaderProbe.path

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libgpg-error-0"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["gpg-error"]
	}

	Probes.PathProbe {
		id: libgpg_errorProbe

        names: qbs.targetOS.contains("windows") ? ["libgpg-error-0"] : ["libgpg-error"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: gpg_errorHeaderProbe

		names: ["gpg-error.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }
}
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
