import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: project.staticExtensions ? ["staticlibrary"] : ["dynamiclibrary"]

	cutehmiType: "extension"

	targetName: name

	condition: project.buildExtensions

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

	property stringList qmlImportPaths: [cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionInstallDirname]	// QML import paths for QtCreator.

	property string macroName: baseName.toUpperCase().replace(/\./g, '_')

	Properties {
		condition: qbs.targetOS.contains("windows")
		targetName: name + (qbs.buildVariant.contains("debug") ? "d" : "")
	}

	Properties {
		condition: qbs.targetOS.contains("android")
		targetName: "android_" + name
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

		Depends {
			name: "android_" + product.name
			condition: importingProduct.cutehmiType == "tool" && qbs.targetOS.contains("android")
			cpp.link: false
		}
	}

	Depends { name: "cutehmi.metadata" }
	Depends { name: "cutehmi.dirs" }

	FileTagger {
		patterns: ["*.jpg", "*.svg"]
		fileTags: ["Images"]
	}

	Group {
		name: "Images"
		fileTagsFilter: ["Images"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.extensionInstallDirname
	}

	FileTagger {
		patterns: "*.metainfo"
		fileTags: ["metainfo"]
	}

	Group {
		name: "Metainfo"
		fileTagsFilter: ["metainfo"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}

	FileTagger {
		patterns: "*.js"
		fileTags: ["js"]
	}

	FileTagger {
		patterns: "*.qml"
		fileTags: ["qml"]
	}

	FileTagger {
		patterns: "*.qmltypes"
		fileTags: ["qmltypes"]
	}

	FileTagger {
		patterns: "qmldir"
		fileTags: ["qmldir"]
	}

	Group {
		name: "QML"
		fileTagsFilter: ["js", "qml", "qmldir", "qmltypes"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}

	FileTagger {
		patterns: ["LICENSE", "README.md"]
		fileTags: ["ReadmeFiles"]
	}

	Group {
		name: "Readme files"
		fileTagsFilter: ["ReadmeFiles"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}
}

//(c)C: Copyright © 2018-2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
