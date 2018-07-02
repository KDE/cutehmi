import qbs 1.0
import qbs.Probes
import qbs.FileInfo

Module {
	cpp.libraryPaths: FileInfo.cleanPath(libiconvProbe.path)

	cpp.includePaths: FileInfo.cleanPath(iconvHeaderProbe.path)

	Properties {
		condition: qbs.targetOS.contains("windows")
		cpp.dynamicLibraries: ["libiconv-2"]
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["iconv"]
	}

	property bool found: libiconvProbe.found && iconvHeaderProbe.found

	property bool available: found

	property string libiconvPath: libiconvProbe.filePath

	property string includePath: iconvHeaderProbe.path

	Probes.PathProbe {
		id: libiconvProbe

        names: qbs.targetOS.contains("windows") ? ["libiconv-2"] : ["libiconv"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/libiconv/lib"])
	}

	Probes.PathProbe {
		id: iconvHeaderProbe

		names: ["iconv.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/libiconv/include"])
	}

	Group {
		name: "Libiconv"
		files: cutehmi.libiconv.libiconvPath
		condition: cutehmi.libiconv.libiconvPath
		qbs.install: true
		qbs.installDir: cutehmi.dirs.moduleInstallDir
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }
}
