import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: []

	cutehmiType: "example"

	baseName: name

	condition: project.buildExamples

	cpp.includePaths: [cutehmi.dirs.externalIncludeDir]

	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	property string installPrefix: parent.parent.name

	property string installDir: cutehmi.dirs.examplesInstallDirname + "/" + installPrefix + "/" + FileInfo.baseName(sourceDirectory)

	FileTagger {
		patterns: "*.png"
		fileTags: ["png"]
	}

	FileTagger {
		patterns: "*.svg"
		fileTags: ["svg"]
	}

	Group {
		name: "Images"
		fileTagsFilter: ["png", "svg"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: installDir
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

	FileTagger {
		patterns: "*.xml"
		fileTags: ["xml"]
	}

	Group {
		name: "XML"
		fileTagsFilter: ["xml"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}

	Depends { name: "cutehmi.dirs" }
}

//(c)MP: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
