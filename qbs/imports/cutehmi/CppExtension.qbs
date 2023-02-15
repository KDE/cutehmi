import qbs
import qbs.FileInfo

import "Extension.qbs" as Extension

/**
  C++ extension product. This item sets up properties for extensions that use C++ code (either if C++ code is going to be used for a
  library or QML plugin, or both).

  @note Set `type` explicitly to `[]` if the library contains only header files. Otherwise Qbs `cpp` module will trigger a linker.
  */
Extension {
	type: project.buildBinaries ? (project.staticExtensions ? ["staticlibrary"] : ["dynamiclibrary"]) : []

	targetName: name
	Properties {
		condition: qbs.targetOS.contains("windows")
		targetName: name + (qbs.buildVariant.contains("debug") ? "d" : "")
	}
	Properties {
		condition: qbs.targetOS.contains("android")
		targetName: "android_" + name
	}

	extensionType: "cpp"

	property string macroName: baseName.toUpperCase().replace(/\./g, '_')

	Export {
		cpp.defines: {
			var defines = [exportingProduct.macroName + "_" + exportingProduct.major + "_" + exportingProduct.minor]
			if (!project.staticExtensions)
				defines.push(exportingProduct.macroName + "_DYNAMIC")
			if (project.buildTests)
				defines.push(exportingProduct.macroName + "_TEST")
			return defines
		}

		//<qbs-cutehmi.cpp-1.workaround target="Qbs" cuase="missing">
		// Qbs does not allow Export within Module items. Using 'cutehmi.cpp.exportedIncludePaths' property to export include paths.
		cpp.includePaths: exportingProduct.cutehmi.cpp.exportedIncludePaths
		// Instead of:
		// cpp.includePaths: [sourceDirectory + "/include"]
		//</qbs-cutehmi.cpp-1.workaround>

		Depends { name: "cpp" }

		Depends {
			name: "android_" + exportingProduct.name
			condition: importingProduct.cutehmiType == "tool" && qbs.targetOS.contains("android")
			cpp.link: false
		}
	}

	Depends { name: "cpp" }
	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}
	cpp.defines: {
		var defines = [macroName + "_BUILD"]
		if (!project.staticExtensions)
			defines.push(macroName + "_DYNAMIC")
		if (project.buildTests)
			defines.push(macroName + "_TESTS")
		return base.concat(defines)
	}
	cpp.includePaths: [cutehmi.conventions.includeDir, cutehmi.dirs.externalIncludeDir]
	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	Depends { name: "cutehmi.cpp" }
	//<qbs-cutehmi.cpp-1.workaround target="Qbs" cuase="missing">
	// Qbs does not allow Export within Module items. Using 'cutehmi.cpp.exportedIncludePaths' property to export include paths.
	cutehmi.cpp.exportedIncludePaths: [sourceDirectory + "/include"]
	//</qbs-cutehmi.cpp-1.workaround>

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.extensionsInstallSubdir
	}
}

//(c)C: Copyright © 2019-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
