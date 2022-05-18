import qbs
import qbs.Environment
import qbs.File
import qbs.TextFile

/**
  This module generates 'qmltypes' artifact.
  */
Module {
	additionalProductTypes: ["cutehmi.qmltypes"]

	property string qmlplugindumpProgram: "cutehmi.qmlplugindump.0"

	property string qmlplugindumpFallbackProgram: "qmlplugindump"

	Depends { name: "Qt.core" }

	Depends { name: "cutehmi.dirs" }

	Rule {
		// Android builds are not supported by this module.
		condition: !qbs.targetOS.contains("android")

		multiplex: true
		explicitlyDependsOn: product.type.contains("dynamiclibrary") ? ["qml", "js", "qmldir", "dynamiclibrary"] : ["qml", "js", "qmldir"]
		//<cutehmi.qmlplugindump.0-1.workaround target="Qt" cause="missing">
		// Due to workaround output artifact explicitly depends on "qmlplugindump", which is a tag provided by "cutehmi.qmlplugindump.0" tool.
		explicitlyDependsOnFromDependencies: ["qmlplugindump", "qml", "js", "qmldir", "dynamiclibrary"]
		///</cutehmi.qmlplugindump.0-1.workaround>

		prepare: {
			var qmlplugindumpProgram = product.cutehmi.qmltypes.qmlplugindumpProgram
			var qmlplugindumpFallbackProgram = product.cutehmi.qmltypes.qmlplugindumpFallbackProgram

			//<qbs-cutehmi.qmltypes-2.workaround target="Qbs" cause="missing">
			// Checking if directory exists as a dirty workaround to check if `--no-install` options has been set from command line.
			if (!File.exists(product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionsInstallSubdir)) {
				var dumpCmd = new JavaScriptCommand()
				dumpCmd.description = "can not generate artifact '" + output.filePath + "' when '--no-install` options has been set from command line"
				dumpCmd.sourceCode = function () {
					console.warn("Can not create '" + output.filePath + "' artifact when '--no-install` options has been set from command line (tip: remove your build directory entirely after unchecking '--no-install' option)")
				}
			} else {
				//<cutehmi.qmlplugindump.0-1.workaround target="Qt" cause="missing">
				// Custom built 'cutehmi.qmlplugindump.0' is used to generate qmltypes in debug builds.
				if (explicitlyDependsOn["qmlplugindump"] !== undefined) {
					var dumpCmd = new Command(explicitlyDependsOn["qmlplugindump"][0].filePath,
											  ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionsInstallSubdir])
					dumpCmd.description = "invoking '" + qmlplugindumpProgram + "' program to generate '" + output.filePath + "'"
				} else {
					console.warn("Tool '" + qmlplugindumpProgram + "' unavailable")
					if ((product.qbs.buildVariant == "debug") && product.qbs.hostOS.contains("windows")) {
						var dumpCmd = new JavaScriptCommand()
						dumpCmd.description = "can not generate artifact '" + output.filePath + "' without '" + qmlplugindumpProgram + "' in debug mode"
						dumpCmd.qmlplugindumpProgram = qmlplugindumpProgram
						dumpCmd.sourceCode = function () {
							console.warn("Can not create '" + output.filePath + "' artifact without '" + qmlplugindumpProgram + "' in debug mode")
						}
					} else {
						console.warn("Falling back to 'qmlplugindump' provided by Qt, which may not work for debug builds")
						var dumpCmd = new Command(product.Qt.core.binPath + "/" + qmlplugindumpFallbackProgram, ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionsInstallSubdir])
						dumpCmd.description = "invoking '" + qmlplugindumpFallbackProgram + "' program to generate " + output.filePath
					}
				}
				///</cutehmi.qmlplugindump.0-1.workaround>
			}
			//</qbs-cutehmi.qmltypes-2.workaround>
			dumpCmd.workingDirectory = product.cutehmi.dirs.installDir
			var paths = product.cpp.libraryPaths.concat([product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionsInstallSubdir,
														 product.Qt.core.libPath,
														 product.Qt.core.binPath,	// On Windows runtime libraries are installed to 'binPath' and not 'libPath'.
														]).join(product.qbs.pathListSeparator)
			if (product.qbs.hostOS.contains("windows"))
				dumpCmd.environment = ["PATH=" + paths + product.qbs.pathListSeparator + Environment.getEnv("PATH")]
			else if (product.qbs.hostOS.contains("macos"))
				dumpCmd.environment = ["DYLD_LIBRARY_PATH=" + paths + product.qbs.pathListSeparator + Environment.getEnv("DYLD_LIBRARY_PATH")]
			else
				dumpCmd.environment = ["LD_LIBRARY_PATH=" + paths + product.qbs.pathListSeparator + Environment.getEnv("LD_LIBRARY_PATH")]
			dumpCmd.highlight = "codegen"
			dumpCmd.stdoutFilePath = product.sourceDirectory + "/plugins.qmltypes"
			return [dumpCmd]
		}

		Artifact {
			filePath: product.sourceDirectory + "/plugins.qmltypes"
			fileTags: ["cutehmi.qmltypes", "qmltypes"]
		}
	}
}

//(c)C: Copyright © 2018-2022, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
