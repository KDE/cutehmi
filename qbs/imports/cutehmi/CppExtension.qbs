import qbs
import qbs.FileInfo

import "Extension.qbs" as Extension

/**
  C++ extension product. This item sets up properties for extensions that use C++ code (either if C++ code is going to be used for a
  library or QML plugin, or both).
  */
Extension {
	type: project.staticExtensions ? ["staticlibrary"] : ["dynamiclibrary"]

	targetName: name
	Properties {
		condition: qbs.targetOS.contains("windows")
		targetName: name + (qbs.buildVariant.contains("debug") ? "d" : "")
	}
	Properties {
		condition: qbs.targetOS.contains("android")
		targetName: "android_" + name
	}

	property string macroName: baseName.toUpperCase().replace(/\./g, '_')

	Export {
		cpp.defines: {
			var defines = [product.macroName + "_" + product.major + "_" + product.minor]
			if (!project.staticExtensions)
				defines.push(product.macroName + "_DYNAMIC")
			if (project.buildTests)
				defines.push(product.macroName + "_TEST")
			return defines
		}

		//<qbs-cutehmi.cpp-1.workaround target="Qbs" cuase="missing">
		// Qbs does not allow Export within Module items. Using 'cutehmi.cpp.exportedIncludePaths' property to export include paths.
		cpp.includePaths: product.cutehmi.cpp.exportedIncludePaths
		// Instead of:
		// cpp.includePaths: [sourceDirectory + "/include"]
		//</qbs-cutehmi.cpp-1.workaround>

		Depends { name: "cpp" }

		Depends {
			name: "android_" + product.name
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
	cpp.includePaths: [product.sourceDirectory + "/include", cutehmi.dirs.externalIncludeDir]
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
		qbs.installDir: cutehmi.dirs.extensionInstallSubdir
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
