import qbs 1.0
import qbs.Probes
import qbs.FileInfo

Module {
	cpp.libraryPaths: FileInfo.cleanPath(libgcryptProbe.path)

	cpp.includePaths: FileInfo.cleanPath(gcryptHeaderProbe.path)

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libgcrypt-20"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
        cpp.dynamicLibraries: ["gcrypt"]
	}

	property bool found: libgcryptProbe.found && gcryptHeaderProbe.found

	property bool available: found && cutehmi.libgpg_error.available

	property string libgcryptPath: libgcryptProbe.filePath

	property string includePath: gcryptHeaderProbe.path

	Probes.PathProbe {
		id: libgcryptProbe

		names: qbs.targetOS.contains("windows") ? ["libgcrypt-20"] : ["libgcrypt"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: gcryptHeaderProbe

		names: ["gcrypt.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.libgpg_error" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
