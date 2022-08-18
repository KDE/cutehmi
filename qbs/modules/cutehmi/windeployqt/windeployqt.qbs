import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment

/**
  This module uses _windeployqt_ program to collect Qt runtime for Windows deployment.

  @note `cutehmi.dirs.installDir` is used as a working directory so all properties specifying directories for _windeployqt_ should be
  either relative to `cutehmi.dirs.installDir` or absolute.
  */
Module {
	additionalProductTypes: ["cutehmi.windeployqt"]

	property string windeployqtProgram: "windeployqt"

	property string qmake: undefined

	/**
	  Defines where collected files are being copied. This can be useful to distinguish Qt runtime from project artifacts. Uses
	  location of the binary if undefined.
	  */
	property string dir: undefined

	property string libdir: undefined

	property string plugindir: product.cutehmi.windeployqt.dir !== undefined ? product.cutehmi.windeployqt.dir + "/plugins"
																			 : product.cutehmi.dirs.toolsInstallSubdir + "/plugins"

	property bool debug: false

	property bool release: false

	property bool pdb: false

	property bool force: false

	property bool dryRun: false

	property bool noPatchqt: false

	property bool ignoreLibraryErrors: false

	property bool noPlugins: false

	property bool noLibraries: false

	property string qmldir: product.dedicatedInstallSubdir !== undefined ? product.dedicatedInstallSubdir
																		 : undefined

	property string qmlimport: undefined

	property bool noQuickImport: false

	property string languages: undefined

	property bool noTranslations: false

	property bool noSystemD3dCompiler: false

	property bool compilerRuntime: false

	property bool noVirtualkeyboard: false

	property bool noCompilerRuntime: false

	property bool json: false

	property bool noOpenglSw: false

	property string list: undefined

	property int verbose: undefined

	Depends { name: "Qt.core" }

	Depends { name: "cutehmi.dirs" }

	Rule {
		condition: qbs.targetOS.contains("windows")

		//<qbs-cutehmi.windeployqt-1.workaround target="windeployqt" cause="missing">
		// Simple QML extensions are using CuteHMI.Workarounds.windeployqt.0 as their binary file.
		inputs: product.type.contains("dynamiclibrary") ? ["dynamiclibrary"]
														: product.cutehmiType === "tool" ? ["application"]
																						 : []
		// Due to the workaround the dynamic library provided by "CuteHMI.Workarounds.windeployqt.0" extension is and input for simple QML extensions.
		inputsFromDependencies: ["CuteHMI.Workarounds.windeployqt.0.dynamiclibrary"]
		explicitlyDependsOn: ["qml", "js", "qmldir"]
		explicitlyDependsOnFromDependencies: ["qml", "js", "qmldir", "dynamiclibrary"]
		//</qbs-cutehmi.windeployqt-1.workaround>

		prepare: {
			var windeployqtProgram = product.cutehmi.windeployqt.windeployqtProgram

			// Checking if directory exists as a dirty workaround to check if `--no-install` options has been set from command line.
			if (!File.exists(product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionsInstallSubdir)) {
				var cmd = new JavaScriptCommand()
				cmd.description = "can not invoke '" + windeployqtProgram + "' when '--no-install` options has been set from command line"
				cmd.sourceCode = function () {
					console.warn("Can not invoke '" + windeployqtProgram + "' when '--no-install` options has been set from command line (tip: remove your build directory entirely after unchecking '--no-install' option)")
				}
			} else {
				var cmdArgs = []

				if (product.cutehmi.windeployqt.qmake !== undefined)
					cmdArgs.push("--qmake", product.cutehmi.windeployqt.qmake)

				if (product.cutehmi.windeployqt.dir !== undefined)
					cmdArgs.push("--dir", product.cutehmi.windeployqt.dir)

				if (product.cutehmi.windeployqt.libdir !== undefined)
					cmdArgs.push("--libdir", product.cutehmi.windeployqt.libdir)

				if (product.cutehmi.windeployqt.plugindir !== undefined)
					cmdArgs.push("--plugindir", product.cutehmi.windeployqt.plugindir)

				if (product.cutehmi.windeployqt.debug)
					cmdArgs.push("--debug")

				if (product.cutehmi.windeployqt.release)
					cmdArgs.push("--release")

				if (product.cutehmi.windeployqt.pdb)
					cmdArgs.push("--pdb")

				if (product.cutehmi.windeployqt.force)
					cmdArgs.push("--force")

				if (product.cutehmi.windeployqt.dryRun)
					cmdArgs.push("--dry-run")

				if (product.cutehmi.windeployqt.noPatchqt)
					cmdArgs.push("--no-patchqt")

				if (product.cutehmi.windeployqt.ignoreLibraryErrors)
					cmdArgs.push("----ignore-library-errors")

				if (product.cutehmi.windeployqt.noPlugins)
					cmdArgs.push("--no-plugins")

				if (product.cutehmi.windeployqt.noLibraries)
					cmdArgs.push("--no-libraries")

				if (product.cutehmi.windeployqt.qmldir !== undefined) {
					var qmldirPath = FileInfo.isAbsolutePath(product.cutehmi.windeployqt.qmldir) ? product.cutehmi.windeployqt.qmldir
																								 : product.cutehmi.dirs.installDir + "/" + product.cutehmi.windeployqt.qmldir
					if (File.exists(qmldirPath))
						cmdArgs.push("--qmldir", product.cutehmi.windeployqt.qmldir)
				}

				if (product.cutehmi.windeployqt.qmlimport !== undefined)
					cmdArgs.push("--qmlimport", product.cutehmi.windeployqt.qmlimport)

				if (product.cutehmi.windeployqt.noQuickImport)
					cmdArgs.push("--no-quick-import")

				if (product.cutehmi.windeployqt.languages !== undefined)
					cmdArgs.push("--languages", product.cutehmi.windeployqt.languages)

				if (product.cutehmi.windeployqt.noTranslations)
					cmdArgs.push("--no-translations")

				if (product.cutehmi.windeployqt.noSystemD3dCompiler)
					cmdArgs.push("--no-system-d3d-compiler")

				if (product.cutehmi.windeployqt.compilerRuntime)
					cmdArgs.push("--compiler-runtime")

				if (product.cutehmi.windeployqt.noVirtualkeyboard)
					cmdArgs.push("--no-virtualkeyboard")

				if (product.cutehmi.windeployqt.noCompilerRuntime)
					cmdArgs.push("--no-compiler-runtime")

				if (product.cutehmi.windeployqt.json)
					cmdArgs.push("--json")

				if (product.cutehmi.windeployqt.noOpenglSw)
					cmdArgs.push("--no-opengl-sw")

				if (product.cutehmi.windeployqt.list !== undefined)
					cmdArgs.push("--list", product.cutehmi.windeployqt.list)

				if (product.cutehmi.windeployqt.verbose !== undefined)
					cmdArgs.push("--verbose", product.cutehmi.windeployqt.verbose)

				var binaryFile = product.cutehmiType == "tool" ? product.cutehmi.dirs.toolsInstallSubdir + "/" + input.fileName
															   : product.cutehmi.dirs.extensionsInstallSubdir + "/" + input.fileName
				cmdArgs.push(binaryFile)

				var cmd = new Command(product.Qt.core.binPath + "/" + windeployqtProgram, cmdArgs)
				cmd.jobPool = "windeployqt"
				cmd.description = "invoking '" + windeployqtProgram
			}
			cmd.workingDirectory = product.cutehmi.dirs.installDir
			var paths = product.cpp.libraryPaths.concat([product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionsInstallSubdir,
														 product.Qt.core.libPath,
														 product.Qt.core.binPath,	// On Windows runtime libraries are installed to 'binPath' and not 'libPath'.
														]).join(product.qbs.pathListSeparator)
			cmd.environment = ["PATH=" + paths + product.qbs.pathListSeparator + Environment.getEnv("PATH")]
			cmd.highlight = "codegen"
			return [cmd]
		}

		outputFileTags: ["cutehmi.windeployqt"]
	}

	JobLimit {
		jobPool: "windeployqt"
		jobCount: 1
	}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
