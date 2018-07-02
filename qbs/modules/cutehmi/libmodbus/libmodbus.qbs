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

		names: ["libmodbus-5"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/libmodbus/lib"])
	}

	Probes.PathProbe {
		id: modbusHeaderProbe

		names: ["modbus/modbus.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/libmodbus/include"])
	}

	Group {
		name: "Libmodbus"
		files: cutehmi.libmodbus.libmodbusPath
		condition: cutehmi.libmodbus.libmodbusPath
		qbs.install: true
		qbs.installDir: cutehmi.dirs.moduleInstallDir
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }
}
