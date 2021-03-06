import qbs

/**
  This module generates 'rcc' artifact.
  */
Module {
	additionalProductTypes: ["cutehmi.rcc"]

	property string rccProgram: "rcc"

	Depends { name: "Qt.core" }

	Rule {
		inputs: ["qrc"]
		outputFileTags: ["rcc", "cutehmi.rcc"]
		outputArtifacts: {
			return [{
						filePath: input.completeBaseName + ".rcc",
						fileTags: ["rcc", "cutehmi.rcc"]
			}]
		}

		prepare: {
			var rccProgram = product.cutehmi.rcc.rccProgram
			var args = [input.filePath, "-binary", "-o", output.filePath]
			 if (input.Qt.core.enableBigResources)
				 args.push("-pass", "1")
			 var cmd = new Command(product.Qt.core.binPath + '/rcc', args);
			 cmd.highlight = 'codegen'
			 cmd.description = "invoking '" + rccProgram + "' program to generate '" + output.filePath + "'"
			 return cmd
		}
	}
}
