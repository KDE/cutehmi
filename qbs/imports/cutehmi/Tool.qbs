import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

/**
  Tool product.
  */
CommonProduct {
	type: project.buildBinaries ? (project.buildApk ? "android.apk" : "application") : []

	cutehmiType: "tool"

	targetName: qbs.buildVariant.contains("debug") ? name + ".debug" : name

	condition: project.buildTools

	baseName: cutehmi.conventions.functions.baseName(name)

	major: cutehmi.conventions.functions.major(name)

	Depends { name: "cpp" }
	Properties {
		readonly property string extensionsRelativePath: FileInfo.relativePath(cutehmi.dirs.installDir + "/" + cutehmi.dirs.toolsInstallSubdir, cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionsInstallSubdir)

		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN" + (extensionsRelativePath === "." ? "" : "/" + extensionsRelativePath)
	}
	cpp.includePaths: [
		cutehmi.dirs.externalIncludeDir,
		product.sourceDirectory + "/" + cutehmi.conventions.functions.includesSubdir(product.name)
	]
	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	Depends { name: "cutehmi.android.package"; condition: project.buildApk }
	Depends { name: "cutehmi.android.deployInstall"; condition: qbs.targetOS.contains("android") }

	Depends { name: "cutehmi.cpp" }

	Depends { name: "cutehmi.conventions" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.metadata" }

	Depends { name: "cutehmi.windeployqt"; condition: project.windeployqt }

	Export {
		Depends { name: "cpp" }

		cpp.includePaths: [exportingProduct.sourceDirectory + "/include"]
	}

	Group {
		name: "Application"
		fileTagsFilter: "application"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.toolsInstallSubdir
	}

	Group {
		name: "Translations"
		fileTagsFilter: ["qm"]
		qbs.install: true
		qbs.installDir: cutehmi.dirs.translationsInstallSubdir
	}

	Group {
		name: "Metadata"
		fileTagsFilter: ["cutehmi.metadata.json"]
		qbs.install: true
		qbs.installDir: cutehmi.dirs.metadataInstallSubdir
	}
}

//(c)C: Copyright © 2018-2024, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
