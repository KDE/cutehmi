import qbs
import qbs.Environment
import qbs.File

/**
  This module generates 'qmltypes' artifact.
  */
Module {
	additionalProductTypes: ["qmltypes"]

	Depends { name: "Qt.core" }

	Depends { name: "cutehmi.dirs" }

	readonly property bool qmlplugindumpAvailable: {
		// Unfortunately validate script is not applicable here, because it seems to run before 'present' property is set to correct value.
		if (!product.cutehmi_qmlplugindump.present)
			console.error("Can not use 'cutehmi.qmltypes' module without 'cutehmi_qmlplugindump' tool.")

		return product.cutehmi_qmlplugindump.present
	}

	Rule {
		// Android builds are not supported by this module.
		//<qbs-cutehmi.qmltypes-2.workaround target="Qbs" cause="missing">
		// Checking if directory exists as a dirty workaround to check if `--no-install` options has been set from command line.
		condition: !qbs.targetOS.contains("android") && File.exists(product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallSubdir) && qmlplugindumpAvailable
		//</qbs-cutehmi.qmltypes-2.workaround>

		multiplex: true
		explicitlyDependsOn: product.type.contains("dynamiclibrary") ? ["qml", "js", "qmldir", "dynamiclibrary"] : ["qml", "js", "qmldir"]
		//<cutehmi_qmlplugindump-1.workaround target="Qt" cause="missing">
		explicitlyDependsOnFromDependencies: ["qmlplugindump"]
		///</cutehmi_qmlplugindump-1.workaround>

		prepare: {
			//<cutehmi_qmlplugindump-1.workaround target="Qt" cause="missing">
			// Custom built cutehmi_qmlplugindump is used to generate qmltypes in debug builds.
			var dumpCmd = new Command(explicitlyDependsOn["qmlplugindump"][0].filePath,
									  ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionInstallSubdir]);
			// Instead of:
			// var dumpCmd = new Command(product.Qt.core.binPath + "/qmlplugindump", ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionInstallSubdir]);
			///</cutehmi_qmlplugindump-1.workaround>
			dumpCmd.workingDirectory = product.cutehmi.dirs.installDir
			var paths = product.cpp.libraryPaths.concat([product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallSubdir,
														 product.Qt.core.libPath,
														 product.Qt.core.binPath,	// On Windows runtime libraries are installed to 'binPath' and not 'libPath'.
														]).join(product.qbs.pathListSeparator)
			if (product.qbs.targetOS.contains("windows"))
				dumpCmd.environment = ["PATH=" + paths + product.qbs.pathListSeparator + Environment.getEnv("PATH")]
			else if (product.qbs.targetOS.contains("macos"))
				dumpCmd.environment = ["DYLD_LIBRARY_PATH=" + paths + product.qbs.pathListSeparator + Environment.getEnv("DYLD_LIBRARY_PATH")]
			else
				dumpCmd.environment = ["LD_LIBRARY_PATH=" + paths + product.qbs.pathListSeparator + Environment.getEnv("LD_LIBRARY_PATH")]
			dumpCmd.description = "invoking 'qmlplugindump' program to generate " + product.sourceDirectory + "/plugins.qmltypes";
			dumpCmd.highlight = "codegen"
			dumpCmd.stdoutFilePath = product.sourceDirectory + "/plugins.qmltypes"
			return [dumpCmd]
		}

		Artifact {
			filePath: product.sourceDirectory + "/plugins.qmltypes"
			fileTags: ["qmltypes"]
		}
	}
}

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
