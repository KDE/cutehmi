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

	property string installSourceBase: sourceDirectory

	property string dedicatedInstallSubdir: cutehmi.dirs.extensionsInstallSubdir + "/" + FileInfo.relativePath(cutehmi.dirs.extensionsSourceDir, sourceDirectory)

	//<qbs-imports-cutehmi-3.workaround target="Qbs" cuase="bug_or_missing">
	// Using 'qmlImportPaths' instead of 'qmlDesignerImportPaths' for puppets.
	// property stringList qmlDesignerImportPaths: [cutehmi.dirs.installDir + "/" + cutehmi.dirs.puppetsInstallSubdir]	// QML import paths for QtCreator's Designer.
	property stringList qmlImportPaths: [cutehmi.dirs.installDir + "/" + cutehmi.dirs.puppetsInstallSubdir,
										 cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionsInstallSubdir]	// QML import paths for QtCreator.
	//</qbs-imports-cutehmi-3.workaround>

	Depends { name: "cutehmi.dirs" }

	//<cutehmi.qmlplugindump.0-1.workaround target="Qt" cause="missing">
	Depends { name: "cutehmi.qmlplugindump.0"; required: false }
	//</cutehmi.qmlplugindump.0-1.workaround>

	Depends { name: "cutehmi.conventions" }

	Depends { name: "cutehmi.metadata" }

	FileTagger {
		patterns: ["*.bdf", "*.otf", "*.pcf", "*.ttf"]
		fileTags: ["Fonts"]
	}

	Group {
		name: "Fonts"
		fileTagsFilter: ["Fonts"]
		qbs.install: true
		qbs.installSourceBase: installSourceBase
		qbs.installDir: dedicatedInstallSubdir
	}

	FileTagger {
		patterns: ["*.bmp", "*.gif", "*.ico", "*.jpg", "*.png", "*.svg"]
		fileTags: ["Images"]
	}

	Group {
		name: "Images"
		fileTagsFilter: ["Images"]
		qbs.install: true
		qbs.installSourceBase: installSourceBase
		qbs.installDir: dedicatedInstallSubdir
	}

	FileTagger {
		patterns: "*.metainfo"
		fileTags: ["metainfo"]
	}

	Group {
		name: "Metainfo"
		fileTagsFilter: ["metainfo"]
		qbs.install: true
		qbs.installSourceBase: installSourceBase
		qbs.installDir: dedicatedInstallSubdir
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
		qbs.installSourceBase: installSourceBase
		qbs.installDir: dedicatedInstallSubdir
	}

	FileTagger {
		patterns: ["LICENSE", "README.md", "*.txt"]
		fileTags: ["ReadmeFiles"]
	}

	Group {
		name: "Readme files"
		fileTagsFilter: ["ReadmeFiles"]
		qbs.install: true
		qbs.installSourceBase: installSourceBase
		qbs.installDir: dedicatedInstallSubdir
	}

	Group {
		name: "Translations"
		fileTagsFilter: ["qm"]
		qbs.install: true
		qbs.installDir: cutehmi.dirs.translationsInstallSubdir
	}

	FileTagger {
		patterns: "*.ini"
		fileTags: ["ini"]
	}

	Group {
		name: "Ini files"
		fileTagsFilter: ["ini"]
		qbs.install: true
		qbs.installSourceBase: installSourceBase
		qbs.installDir: dedicatedInstallSubdir
	}

	FileTagger {
		patterns: ["*.sql"]
		fileTags: ["sql"]
	}

	Group {
		name: "SQL"
		fileTagsFilter: ["sql"]
		qbs.install: true
		qbs.installSourceBase: installSourceBase
		qbs.installDir: dedicatedInstallSubdir
	}

	Group {
		name: "Metadata"
		fileTagsFilter: ["cutehmi.metadata.json"]
		qbs.install: true
		qbs.installDir: cutehmi.dirs.metadataInstallSubdir
	}

	FileTagger {
		patterns: ["*.rcc"]
		fileTags: ["rcc"]
	}

	Group {
		name: "Binary resource files"
		fileTagsFilter: ["rcc"]
		qbs.install: true
		qbs.installDir: dedicatedInstallSubdir
	}
}

//(c)C: Copyright © 2018-2021, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
