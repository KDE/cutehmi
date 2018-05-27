import qbs
import qbs.Environment
import qbs.Utilities

import "functions.js" as Functions

/**
  This module generates 'plugins.qmltypes' artifact.
  */
Module {
	additionalProductTypes: ["qmltypes"]

	condition: qbs.targetOS.contains("windows")

	Depends { name: "Qt.core" }

	Rule {
		multiplex: true
		inputs: ["qml", "dynamiclibrary"]

		prepare: {
			var dumpCmd = new Command(product.Qt.core.binPath + "/qmlplugindump", ["-nonrelocatable", product.name, product.major + "." + product.minor, "QML"]);
			dumpCmd.workingDirectory = product.qbs.installRoot
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
