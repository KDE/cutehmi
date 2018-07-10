import qbs 1.0
import qbs.Probes
import qbs.FileInfo

Module {
	cpp.libraryPaths: FileInfo.cleanPath(libmodbusProbe.path)

	cpp.includePaths: FileInfo.cleanPath(modbusHeaderProbe.path)

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libmodbus-5"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["modbus"]
	}

	property bool found: libmodbusProbe.found && modbusHeaderProbe.found

	property bool available: found

	property string libmodbusPath: libmodbusProbe.filePath

	property string includePath: modbusHeaderProbe.path

	Probes.PathProbe {
		id: libmodbusProbe

        names: qbs.targetOS.contains("windows") ? ["libmodbus-5"] : ["libmodbus"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
	}

	Probes.PathProbe {
		id: modbusHeaderProbe

		names: ["modbus/modbus.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
