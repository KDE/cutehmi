import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

/**
  Extension product. This item denotes pure QML extension. No C++ artifacts are generated for the product. Use CppExtension item if
  extension is using C++ code.
  */
CommonProduct {
	cutehmiType: "extension"

	condition: project.buildExtensions

	baseName: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? name : name.substring(0, name.lastIndexOf(".", name.length - 1))

	major: isNaN(name.substr(name.lastIndexOf(".", name.length - 1) + 1)) ? 1 : Number(name.substr(name.lastIndexOf(".", name.length - 1) + 1))

	property string installDir: cutehmi.dirs.extensionInstallDirname + "/" + FileInfo.relativePath(cutehmi.dirs.extensionsSourceDir, sourceDirectory)

	property stringList qmlImportPaths: [cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionInstallDirname]	// QML import paths for QtCreator.

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.metadata" }

	Depends { name: "cutehmi_qmlplugindump" }

	FileTagger {
		patterns: ["*.bdf", "*.otf", "*.pcf", "*.ttf"]
		fileTags: ["Fonts"]
	}

	Group {
		name: "Fonts"
		fileTagsFilter: ["Fonts"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}

	FileTagger {
		patterns: ["*.bmp", "*.gif", "*.ico", "*.jpg", "*.png", "*.svg"]
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

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
