import qbs
import qbs.Environment
import qbs.Utilities

import "functions.js" as Functions

/**
  This module generates 'plugins.qmltypes' artifact.
  */
Module {
	additionalProductTypes: ["qmltypes"]

	Depends { name: "Qt.core" }

	Depends { name: "cutehmi.dirs" }

	Rule {
	    condition: false // Temporarily disable generation of qmltypes.
		// condition: !qbs.targetOS.contains("android")	// Android builds are not supported by this module.

		multiplex: true
		explicitlyDependsOn: ["qml", "js", "dynamiclibrary"]
		//<cutehmi_qmlplugindump-1.workaround target="Qt" cause="missing">
		explicitlyDependsOnFromDependencies: ["qmlplugindump"]
		///</cutehmi_qmlplugindump-1.workaround>

		prepare: {
			var qmlplugindump = "cutehmi_qmlplugindump"
			if (product.qbs.buildVariant == "debug")
				qmlplugindump += "_debug"
			//<cutehmi_qmlplugindump-1.workaround target="Qt" cause="missing">
			// Custom built cutehmi_qmlplugindump is used to generate qmltypes in debug builds.
			var dumpCmd = new Command(product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.toolInstallDirname + "/" + qmlplugindump,
									  ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionInstallDirname]);
			// Instead of:
			// var dumpCmd = new Command(product.Qt.core.binPath + "/qmlplugindump", ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionInstallDirname]);
			///</cutehmi_qmlplugindump-1.workaround>
			dumpCmd.workingDirectory = product.cutehmi.dirs.installDir // + "/" + product.cutehmi.dirs.extensionInstallDirname
			var paths = product.cpp.libraryPaths.concat([product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallDirname,
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
