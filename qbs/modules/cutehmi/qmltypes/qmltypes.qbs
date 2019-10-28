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
//<workaround id="qbs-cutehmi-qmltypes-1" target="qmlplugindump" cuase="QTBUG-66669">
		condition: qbs.targetOS.contains("windows") && qbs.buildVariant == "release"
//</workaround>

		multiplex: true
		inputs: ["qml", "dynamiclibrary"]

		prepare: {
			var dumpCmd = new Command(product.Qt.core.binPath + "/qmlplugindump", ["-nonrelocatable", product.baseName, product.major + "." + product.minor, product.cutehmi.dirs.extensionInstallDirname]);
			dumpCmd.workingDirectory = product.cutehmi.dirs.installDir
			var paths = product.cpp.libraryPaths.concat([product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallDirname]).join(product.qbs.pathListSeparator)
			if (product.qbs.targetOS.contains("windows"))
				dumpCmd.environment = ["PATH=" + Environment.getEnv("PATH") + product.qbs.pathListSeparator + paths]
			else if (product.qbs.targetOS.contains("macos"))
				dumpCmd.environment = ["DYLD_LIBRARY_PATH=" + Environment.getEnv("DYLD_LIBRARY_PATH") + product.qbs.pathListSeparator + paths]
			else
				dumpCmd.environment = ["LD_LIBRARY_PATH=" + Environment.getEnv("LD_LIBRARY_PATH") + product.qbs.pathListSeparator + paths]
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

//(c)C: Copyright © 2018-2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
