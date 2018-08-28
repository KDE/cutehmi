import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: "dynamiclibrary"

	cutehmiType: "qmlExtension"

	targetName: baseName + "_" + major + (qbs.buildVariant.contains("debug") ? "d" : "")

	baseName: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? name.toLowerCase().replace(/\./g, '_') + "_qml"
																			 : name.substring(0, name.lastIndexOf(".", name.length - 1)).toLowerCase().replace(/\./g, '_') + "_qml"

	major: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? 1 : Number(name.substr(name.lastIndexOf(".", name.length - 1) + 1))

	property string installDir: cutehmi.dirs.qmlExtensionInstallDirname + "/" + FileInfo.relativePath(cutehmi.dirs.qmlSourceDir, sourceDirectory)

	property stringList qmlImportPaths: [qbs.installRoot + "/" + cutehmi.dirs.qmlExtensionInstallDirname]	// QML import paths for QtCreator.

	Properties {
		condition: qbs.targetOS.contains("linux")
		targetName: baseName + "_" + major
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
		qbs.installDir: installDir + "/" + cutehmi.dirs.qmlPluginInstallDirname
	}

	Group {
		name: "QML"
		fileTagsFilter: ["qml", "js", "qmldir", "qmltypes", "metainfo"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
