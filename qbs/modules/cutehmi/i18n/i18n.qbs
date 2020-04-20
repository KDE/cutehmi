import qbs
import qbs.FileInfo
import qbs.TextFile

/**
  This module generates 'cutehmi.i18n.pro' artifact, which then acts as an input for 'lupdate' program, which in turn produces
  translation files, which are compiled by 'lrelease' program into 'qm' files, which can be loaded by an application.
  */
Module {
	additionalProductTypes: ["cutehmi.i18n"]

	/*
	  Unfortunately you can not simply add empty files to the product, cause 'Qt.core' module has a rule, which calls 'lrelease' on
	  every 'ts' file in the product and 'lrelease' triggers error if these files are empty. Additionaly 'lupdate' also triggers
	  errors, when parsing 'pro' file. Instead this property can be used to create new translation file.
	  */
	property stringList additionalTranslations: []

	property bool update: false

	property string lupdateProgram: "lupdate"

	property string lreleaseProgram: "lrelease"

	property bool lreleaseMultiplex: false

	Depends { name: "Qt.core" }

	Depends { name: "cutehmi.dirs" }

	FileTagger {
		patterns: ["*.ts"]
		fileTags: ["ts"]
	}

	FileTagger {
		patterns: "*.js"
		fileTags: ["js"]
	}

	FileTagger {
		patterns: "*.qml"
		fileTags: ["qml"]
	}

	Rule {
		condition: update
		multiplex: true
		inputs: ["qml", "js", "hpp", "cpp", "ts"]

		prepare: {
			var proCmd = new JavaScriptCommand();
			proCmd.description = 'generating ' + output.filePath
			proCmd.highlight = 'codegen';
			proCmd.sourceCode = function() {
				var f = new TextFile(output.filePath, TextFile.WriteOnly);
				try {
					f.writeLine("lupdate_only {")
					if (inputs["hpp"] !== undefined)
						for (var i = 0; i < inputs["hpp"].length; i++)
							f.writeLine("HEADERS += " + FileInfo.relativePath(product.sourceDirectory, inputs["hpp"][i].filePath))
					if (inputs["cpp"] !== undefined)
						for (var i = 0; i < inputs["cpp"].length; i++)
							f.writeLine("SOURCES += " + FileInfo.relativePath(product.sourceDirectory, inputs["cpp"][i].filePath))
					if (inputs["qml"] !== undefined)
						for (var i = 0; i < inputs["qml"].length; i++)
							f.writeLine("SOURCES += " + FileInfo.relativePath(product.sourceDirectory, inputs["qml"][i].filePath))
					if (inputs["js"] !== undefined)
						for (var i = 0; i < inputs["js"].length; i++)
							f.writeLine("SOURCES += " + FileInfo.relativePath(product.sourceDirectory, inputs["js"][i].filePath))
					f.writeLine("}")

					f.writeLine("")
					if (inputs["ts"] !== undefined)
						for (var i = 0; i < inputs["ts"].length; i++)
							f.writeLine("TRANSLATIONS += " + FileInfo.relativePath(product.sourceDirectory, inputs["ts"][i].filePath))
					for (var i = 0; i < product.cutehmi.i18n.additionalTranslations.length; i++)
						f.writeLine("TRANSLATIONS += " + product.cutehmi.i18n.additionalTranslations[i])
				} finally {
					f.close()
				}
			}
			return [proCmd];
		}

		Artifact {
			filePath: product.sourceDirectory + "/cutehmi.i18n.pro"
			fileTags: ["cutehmi.i18n.pro"]
		}
	}

	Rule {
		multiplex: true
		inputs: ["cutehmi.i18n.pro"]

		prepare: {
			var lupdateProgram = product.cutehmi.i18n.lupdateProgram
			var cmd = new Command(product.Qt.core.binPath + '/' + lupdateProgram, ["-verbose", inputs["cutehmi.i18n.pro"][0].filePath])
			cmd.description = "invoking '" + lupdateProgram + "' program"
			cmd.highlight = 'filegen'
			return cmd
		}

		outputFileTags: ["cutehmi.i18n"]
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
