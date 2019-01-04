import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: project.staticExtensions ? ["staticlibrary"] : ["dynamiclibrary"]

	cutehmiType: "extension"

	targetName: name

	baseName: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? name : name.substring(0, name.lastIndexOf(".", name.length - 1))

	major: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? 1 : Number(name.substr(name.lastIndexOf(".", name.length - 1) + 1))

	cpp.defines: {
		var defines = [macroName + "_BUILD"]
		if (!project.staticExtensions)
			defines.push(macroName + "_DYNAMIC")
		if (project.buildTests)
			defines.push(macroName + "_TESTS")
		return base.concat(defines)
	}

	cpp.includePaths: [product.sourceDirectory + "/include", cutehmi.dirs.externalIncludeDir]

	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	property string installDir: cutehmi.dirs.extensionInstallDirname + "/" + FileInfo.relativePath(cutehmi.dirs.extensionsSourceDir, sourceDirectory)

	property stringList qmlImportPaths: [qbs.installRoot + "/" + cutehmi.dirs.extensionInstallDirname]	// QML import paths for QtCreator.

	property string macroName: baseName.toUpperCase().replace(/\./g, '_')

	Properties {
		condition: qbs.targetOS.contains("windows")
		targetName: name + (qbs.buildVariant.contains("debug") ? "d" : "")
	}

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}

	Export {
		cpp.defines: {
			var defines = [product.macroName + "_" + product.major + "_" + product.minor]
			if (!project.staticExtensions)
				defines.push(product.macroName + "_DYNAMIC")
			if (project.buildTests)
				defines.push(product.macroName + "_TEST")
			return defines
		}

		cpp.includePaths: [product.sourceDirectory + "/include"]

		Depends { name: "cpp" }
	}

	Depends { name: "cutehmi.metadata" }
	Depends { name: "cutehmi.dirs" }
	Depends { name: "cutehmi.qmltypes" }

	FileTagger {
		patterns: "*.qml"
		fileTags: ["qml"]
	}

	FileTagger {
		patterns: "*.js"
		fileTags: ["js"]
	}

	FileTagger {
		patterns: "qmldir"
		fileTags: ["qmldir"]
	}

	FileTagger {
		patterns: "*.qmltypes"
		fileTags: ["qmltypes"]
	}

	FileTagger {
		patterns: "*.metainfo"
		fileTags: ["metainfo"]
	}

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.extensionInstallDirname
	}

	Group {
		name: "QML"
		fileTagsFilter: ["qml", "js", "qmldir", "qmltypes", "metainfo"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}

	Group {
		name: "Readme files"
		fileTagsFilter: ["README.md", "LICENSE"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
