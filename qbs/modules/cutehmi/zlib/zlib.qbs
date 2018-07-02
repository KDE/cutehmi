import qbs 1.0
import qbs.Probes
import qbs.FileInfo

Module {
	cpp.libraryPaths: FileInfo.cleanPath(zlibProbe.path)

	cpp.includePaths: FileInfo.cleanPath(zlibHeaderProbe.path)

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["zlib"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["zlib"]
	}

	property bool found: zlibProbe.found && zlibHeaderProbe.found

	property bool available: found

	property string zlibPath: zlibProbe.filePath

	property string includePath: zlibHeaderProbe.path

	Probes.PathProbe {
		id: zlibProbe

		names: ["zlib1"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/zlib/lib"])
	}

	Probes.PathProbe {
		id: zlibHeaderProbe

		names: ["zlib.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/zlib/include"])
	}

	Group {
		name: "Zlib"
		files: cutehmi.zlib.zlibPath
		condition: cutehmi.zlib.zlibPath
		qbs.install: true
		qbs.installDir: cutehmi.dirs.moduleInstallDir
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }
}
