import qbs
import qbs.Environment
import qbs.File
import qbs.TextFile

/**
  This module generates 'qmltypes' artifact.
  */
Module {
	additionalProductTypes: ["cutehmi.qmltypes"]

	Depends { name: "Qt.core" }

	Depends { name: "cutehmi.dirs" }

	Rule {
		// Android builds are not supported by this module.
		condition: !qbs.targetOS.contains("android")

		multiplex: true
		inputs: product.type.contains("dynamiclibrary") ? ["qml", "js", "qmldir", "dynamiclibrary"] : ["qml", "js", "qmldir"]
		//<cutehmi.qmlplugindump.0-1.workaround target="Qt" cause="missing">
		explicitlyDependsOnFromDependencies: ["qmlplugindump"]
		///</cutehmi.qmlplugindump.0-1.workaround>

		prepare: {
			//<qbs-cutehmi.qmltypes-2.workaround target="Qbs" cause="missing">
			// Checking if directory exists as a dirty workaround to check if `--no-install` options has been set from command line.
			if (!File.exists(product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallSubdir)) {
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
											  ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionInstallSubdir])
					dumpCmd.description = "invoking 'cutehmi.qmlplugindump.0' program to generate '" + output.filePath + "'"
				} else {
					console.warn("Tool 'cutehmi.qmlplugindump.0' unavailable")
					if ((product.qbs.buildVariant == "debug") && product.qbs.hostOS.contains("windows")) {
						var dumpCmd = new JavaScriptCommand()
						dumpCmd.description = "can not generate artifact '" + output.filePath + "' without 'cutehmi.qmlplugindump.0' in debug mode"
						dumpCmd.sourceCode = function () {
							console.warn("Can not create '" + output.filePath + "' artifact without 'cutehmi.qmlplugindump.0' in debug mode")
						}
					} else {
						console.warn("Reverting to 'qmlplugindump' provided by Qt, which may not work for debug builds")
						var dumpCmd = new Command(product.Qt.core.binPath + "/qmlplugindump", ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionInstallSubdir])
						dumpCmd.description = "invoking 'qmlplugindump' program to generate " + output.filePath
					}
				}
				///</cutehmi.qmlplugindump.0-1.workaround>
			}
			//</qbs-cutehmi.qmltypes-2.workaround>
			dumpCmd.workingDirectory = product.cutehmi.dirs.installDir
			var paths = product.cpp.libraryPaths.concat([product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallSubdir,
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

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
