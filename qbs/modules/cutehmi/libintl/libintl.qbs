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
		condition: qbs.targetOS.contains("linux")
		cpp.dynamicLibraries: ["intl"]
	}

	property bool found: libintlProbe.found && libintlHeaderProbe.found

	property bool available: found && cutehmi.libiconv.available

	property string libintlPath: libintlProbe.filePath

	property string includePath: libintlHeaderProbe.path

	Probes.PathProbe {
		id: libintlProbe

		names: ["libintl-8"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/gettext/lib"])
	}

	Probes.PathProbe {
		id: libintlHeaderProbe

		names: ["libintl.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/gettext/include"])
	}

	Group {
		name: "Libintl"
		files: cutehmi.libintl.libintlPath
		condition: cutehmi.libintl.libintlPath
		qbs.install: true
		qbs.installDir: cutehmi.dirs.moduleInstallDir
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.libiconv" }
}
