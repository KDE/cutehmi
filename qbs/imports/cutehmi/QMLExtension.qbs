import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: project.staticQMLExtensions ? ["staticlibrary"] : ["dynamiclibrary"]

	cutehmiType: "qmlExtension"

	targetName: name

	baseName: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? name : name.substring(0, name.lastIndexOf(".", name.length - 1))

	major: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? 1 : Number(name.substr(name.lastIndexOf(".", name.length - 1) + 1))

	cpp.includePaths: [cutehmi.dirs.externalIncludeDir]

	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	property string installDir: cutehmi.dirs.qmlExtensionInstallDirname + "/" + FileInfo.relativePath(cutehmi.dirs.qmlSourceDir, sourceDirectory)

	property stringList qmlImportPaths: [qbs.installRoot + "/" + cutehmi.dirs.qmlExtensionInstallDirname]	// QML import paths for QtCreator.

	Properties {
		condition: qbs.targetOS.contains("windows")
		targetName: name + (qbs.buildVariant.contains("debug") ? "d" : "")
	}

	Depends { name: "cutehmi.metadata" }
	Depends { name: "cutehmi.dirs" }
//	Depends { name: "cutehmi.qmltypes" }

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
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
