import qbs
import qbs.FileInfo
import qbs.File

import "CommonProduct.qbs" as CommonProduct

/**
  Android QML plugin product.
  */
CommonProduct {
	name:  "android_" + extensionName

	condition: qbs.targetOS.contains("android")

	type: project.buildBinaries ? ["dynamiclibrary", "android.nativelibrary"] : []

	targetName: extensionName

	cutehmiType: "androidQMLPlugin"

	baseName: isNaN(extensionName.substr(extensionName.lastIndexOf(".", extensionName.length - 1) + 1)) ? extensionName : extensionName.substring(0, extensionName.lastIndexOf(".", extensionName.length - 1))

	files: {
		var namespaceRelativePath = baseName.toLowerCase().replace(/\./g, '/')
		var internalDirPath = sourceDirectory + "/src/" + namespaceRelativePath + "/internal"
		var headerPath = internalDirPath + "/QMLPlugin.hpp"
		var sourcePath = internalDirPath + "/QMLPlugin.cpp"

		return [headerPath, sourcePath]
	}

	property string extensionName

	property string extensionRelativePath: FileInfo.relativePath(cutehmi.dirs.extensionsSourceDir, sourceDirectory)

	Group {
		name: "Android QML plugin"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.extensionsInstallSubdir + "/" + extensionRelativePath
	}

	Depends { name: extensionName }

	Depends { name: "Qt.qml" }

	Depends { name: "cutehmi.cpp" }

	Depends { name: "cutehmi.dirs" }
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
