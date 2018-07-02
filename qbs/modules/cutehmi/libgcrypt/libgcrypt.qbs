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
		cpp.dynamicLibraries: ["libgcrypt"]
	}

	property bool found: libgcryptProbe.found && gcryptHeaderProbe.found

	property bool available: found && cutehmi.libgpg_error.available

	property string libgcryptPath: libgcryptProbe.filePath

	property string includePath: gcryptHeaderProbe.path

	Probes.PathProbe {
		id: libgcryptProbe

		names: ["libgcrypt-20"]
		nameSuffixes: qbs.targetOS.contains("windows") ? [".dll"] : [".so"]
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/libgcrypt/lib"])
	}

	Probes.PathProbe {
		id: gcryptHeaderProbe

		names: ["gcrypt.h"]
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalLibDir + "/libgcrypt/include"])
	}

	Group {
		name: "Libgcrypt"
		files: cutehmi.libgcrypt.libgcryptPath
		condition: cutehmi.libgcrypt.libgcryptPath
		qbs.install: true
		qbs.installDir: cutehmi.dirs.moduleInstallDir
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.libgpg_error" }
}
