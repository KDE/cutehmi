import qbs 1.0
import qbs.Probes
import qbs.FileInfo

Module {
	cpp.libraryPaths: FileInfo.cleanPath(libsshProbe.path)

	cpp.includePaths: FileInfo.cleanPath(libsshHeaderProbe.path)

	property bool found: libsshProbe.found && libsshHeaderProbe.found

	property bool available: found && (qbs.targetOS.contains("windows") ? cutehmi.zlib.available && cutehmi.libgcrypt.available : true)

	property string libsshPath: libsshProbe.filePath

	property string includePath: libsshHeaderProbe.path

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libssh"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["ssh"]
	}

	Probes.PathProbe {
		id: libsshProbe

		names: ["libssh"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: libsshHeaderProbe

		names: ["libssh/libssh.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.zlib"; condition: qbs.targetOS.contains("windows")}
	Depends { name: "cutehmi.libgcrypt"; condition: qbs.targetOS.contains("windows")}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
