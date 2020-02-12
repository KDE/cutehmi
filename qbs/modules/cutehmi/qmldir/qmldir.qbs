import qbs
import qbs.FileInfo
import qbs.Environment
import qbs.Utilities
import qbs.File
import qbs.TextFile

import "prepare.js" as Prepare

/**
  This module generates 'qmldir' artifact. The syntax of 'qmldir' files is described
  [here](https://doc.qt.io/qt-5/qtqml-modules-qmldir.html).
  */
Module {
	additionalProductTypes: ["cutehmi.qmldir"]

	PropertyOptions {
		name: "puppet"
		description: "Determines whether 'qmldir' file is generated for a puppet extension or a normal extension."
	}
	property bool puppet: false

	PropertyOptions {
		name: "modifyGitignore"
		description: "Whether to modify '.gitignore' file. Setting this property to @p true will result in adding a rule to ignore"
		+ " 'qmldir' files. Note that '.gitignore' itself is not treated as an artifact. This means it will be modified only when"
		+ " generation of 'qmldir' artifact is triggered."
	}
	property bool modifyGitignore: true

	PropertyOptions {
		name: "moduleIdentifier"
		description: "Module identifier."
	}
	property string moduleIdentifier: product.cutehmi.conventions.qmlModuleIdentifier

	PropertyOptions {
		name: "major"
		description: "Initial major version. The property represents major version of \<InitialVersion\>, that stands after"
		+ " \<TypeName\> of each QML type entry. It is also used when specyfing major version of plugin binary. By"
		+ " default the property is binded to major version of a product."
	}
	property int major: product.major

	PropertyOptions {
		name: "minor"
		description: "Initial minor version. The property represents minor version of \<InitialVersion\>, that stands after"
		+ " \<TypeName\> of each QML type entry. Default value is 0."
	}
	property int minor: 0

	PropertyOptions {
		name: "qmlPluginFiles"
		description: "Plugin class files. If files with given patterns are present in product file list, then `plugin` and"
		+ " `classname` entries will be generated. Additionaly product type must contain `dynamiclibrary`. Files matching given"
		+ " patterns receive 'cutehmi.qmldir.qmlPlugin' file tag."
	}
	property stringList qmlPluginFiles: [product.cutehmi.conventions.qmlPluginSource]

	PropertyOptions {
		name: "plugins"
		description: "Array of object specyfing a list of plugins that module uses. Default values for a single plugin are provided"
		+ " by 'cutehmi.conventions' Qbs module. Array contains a list of object, which consist of following keys:" + "\n"
		+ " - name - This property stands for `<Name>` in 'qmldir' entry `plugin <Name> [<Path>]`" + "\n"
		+ " - path - A place where plugin library resides. Plugin directory is specified as path relative to the location of"
		+ "          'qmldir' file. This property stands for `<Path>` in 'qmldir' entry `plugin <Name> [<Path>].`" + "\n"
	}
	property var plugins: [
		{
			name: product.cutehmi.conventions.qmlPluginName,
			path: FileInfo.relativePath(product.cutehmi.dirs.installDir + "/" + product.dedicatedInstallSubdir,
										product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallSubdir)
		}]

	PropertyOptions {
		name: "className"
		description: "Plugin class name. For some reason 'qmldir' specification allows for many plugins, but only one plugin class"
		+ " can be specified. This entry is relevant only for static builds though."
	}
	property string className: product.cutehmi.conventions.qmlPluginClassName

	PropertyOptions {
		name: "typeInfo"
		description: "Name of type description file. Setting value to undefined means no typeinfo entry."
	}
	// Better not use 'qmltypes' artifact, because to generate 'qmltypes' one needs 'qmldir' in the first place.
	property string typeInfo: product.cutehmi.conventions.qmlTypeInfo

	PropertyOptions {
		name: "designerSupported"
		description: "Whether Qt Quick Designer is supported by the plugin."
	}
	property bool designerSupported: true

	PropertyOptions {
		name: "additionalEntries"
		description: "Additional entries. List of additional entries that should be written to 'qmldir' file."
	}
	property stringList additionalEntries: []

	PropertyOptions {
		name: "exclude"
		description: "List of file names that should be excluded from 'qmldir'. Regular expressions are used for matching."
	}
	property stringList exclude: []

	PropertyOptions {
		name: "singletons"
		description: "List of QML types that should be marked as singletons."
	}
	property stringList singletons: []

	PropertyOptions {
		name: "filesMap"
		description: "Files map. This property can be used to override default-generated type entries of QML and Javascript files."
		+ " The syntax of these entries is described"
		+ " [here](https://doc.qt.io/qt-5/qtqml-modules-qmldir.html#contents-of-a-module-definition-qmldir-file). A Javascript "
		+ " object should be assigned to this property, where keys denote file names and values contain type definitions. For"
		+ " example, to get folllowing entries in 'qmldir' file:" + "\n"
		+ '```' + "\n"
		+ 'Boletus 4.7 Boletus.qml' + "\n"
		+ 'singleton MagicMushroom 4.4 MagicMushroom.qml' + "\n"
		+ '```' + "\n"
		+ "set the property to the following:" + "\n"
		+ '```' + "\n"
		+ 'cutehmi.qmldir.filesMap: ({"Boletus.qml": "Boletus 4.7", "MagicMushroom.qml": "singleton MagicMushroom 4.4"})' + "\n"
		+ '```' + "\n"
	}
	property var filesMap: ({})

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.conventions" }

	FileTagger {
		patterns: "*.js"
		fileTags: ["cutehmi.qmldir.entity." + product.name]
	}

	FileTagger {
		patterns: "*.qml"
		fileTags: ["cutehmi.qmldir.entity." + product.name]
	}

	FileTagger {
		patterns: qmlPluginFiles
		fileTags: ["cutehmi.qmldir.qmlPlugin"]
	}

	Rule {
		condition: puppet
		//<qbs-cutehmi.qmldirs-2.workaround target="Qbs+QtCreator" cause="bug">
		inputs: ["cutehmi.qmldir.entity." + product.name]	// Note: puppet extension can not have **regular** plugin binary on its own.
		// Instead of:
		// explicitlyDependsOn: ["cutehmi.qmldir.entity." + product.name]

		//<qbs-cutehmi.qmldirs-1.workaround target="Qbs" cause="bug">
		inputsFromDependencies: ["cutehmi.qmldir.entity." + product.originalExtension, "cutehmi.qmldir.qmlPlugin"]
		// Instead of:
		// explicitlyDependsOnFromDependencies: ["cutehmi.qmldir.entity." + product.originalExtension, "cutehmi.qmldir.qmlPlugin"]
		//</qbs-cutehmi.qmldirs-1.workaround>
		//</qbs-cutehmi.qmldirs-2.workaround>

		multiplex: true

		prepare: {
			var qmldirCmd = new JavaScriptCommand();
			qmldirCmd.description = 'generating ' + output.filePath
			qmldirCmd.highlight = 'codegen';
			qmldirCmd.sourceCode = function() {
				var f = new TextFile(output.filePath, TextFile.WriteOnly);
				try {
					// Puppet must pretend to be an original extension.
					var originalProduct
					for (i in product.dependencies)
						if (product.dependencies[i].name === product.originalExtension)
							originalProduct = product.dependencies[i]

					// Path prefix pointing from puppet's dedicated directory to dedicated directory of an extension.
					var prefix = FileInfo.relativePath(product.cutehmi.dirs.installDir + "/" + product.dedicatedInstallSubdir,
													   originalProduct.cutehmi.dirs.installDir + "/" + originalProduct.dedicatedInstallSubdir)
					// Affixate path corrections when looking from puppet's 'qmldir' file for a plugin binary.
					var pluginsCopy = JSON.parse(JSON.stringify(originalProduct.cutehmi.qmldir.plugins))	// JSON.stringify/parse makes a copy.
					for (i in pluginsCopy)
						pluginsCopy[i].path = FileInfo.cleanPath(prefix + "/" + pluginsCopy[i].path)

					// Affixate type info path corrections.
					var typeInfo = FileInfo.cleanPath(prefix + "/" + originalProduct.cutehmi.qmldir.typeInfo)

					var config = {
						moduleIdentifier: originalProduct.cutehmi.qmldir.moduleIdentifier,
						major: originalProduct.cutehmi.qmldir.major,
						minor: originalProduct.cutehmi.qmldir.minor,
						singletons: product.cutehmi.qmldir.singletons.concat(originalProduct.cutehmi.qmldir.singletons),
						output: output,
						outputSourceBase: product.installSourceBase,
						outputInstallDir: product.cutehmi.dirs.installDir + "/" + product.dedicatedInstallSubdir,
						inputs: inputs["cutehmi.qmldir.entity." + originalProduct.name],
						overridingInputs: inputs["cutehmi.qmldir.entity." + product.name],
						inputsSourceBase: originalProduct.installSourceBase,
						inputsInstallDir: originalProduct.cutehmi.dirs.installDir + "/" + originalProduct.dedicatedInstallSubdir,
						excludedInputs: originalProduct.cutehmi.qmldir.exclude,
						filesMap: originalProduct.cutehmi.qmldir.filesMap,
						hasPlugin: originalProduct.type.contains("dynamiclibrary") && inputs["cutehmi.qmldir.qmlPlugin"] !== undefined,
						plugins: product.cutehmi.qmldir.plugins.concat(pluginsCopy),
						className: originalProduct.cutehmi.qmldir.className,
						typeInfo: typeInfo,
						designerSupported: originalProduct.cutehmi.qmldir.designerSupported,
						additionalEntries: originalProduct.cutehmi.qmldir.additionalEntries
					}
					Prepare.writeEntries(f, config)
				} finally {
					f.close()
				}
			}

			var gitignoreCmd = new JavaScriptCommand();
			gitignoreCmd.description = 'generating ' + product.sourceDirectory + '/.gitignore'
			gitignoreCmd.highlight = 'codegen';
			gitignoreCmd.sourceCode = function() {
				var f = new TextFile(product.sourceDirectory + "/.gitignore", TextFile.ReadWrite);
				try {
					Prepare.writeGitignore(f)
				} finally {
					f.close()
				}
			}

			if (product.cutehmi.qmldir.modifyGitignore)
				return [qmldirCmd, gitignoreCmd]
			else
				return [qmldirCmd]
		}

		Artifact {
			filePath: product.installSourceBase + "/qmldir"
			fileTags: ["cutehmi.qmldir", "qmldir"]
		}
	}

	Rule {
		condition: !puppet
		//<qbs-cutehmi.qmldirs-2.workaround target="Qbs+QtCreator" cause="bug">
		inputs: ["cutehmi.qmldir.entity." + product.name, "cutehmi.qmldir.qmlPlugin"]
		// Instead of:
		// explicitlyDependsOn: ["cutehmi.qmldir.entity." + product.name, "cutehmi.qmldir.qmlPlugin"]
		//</qbs-cutehmi.qmldirs-2.workaround>
		multiplex: true

		prepare: {
			var qmldirCmd = new JavaScriptCommand();
			qmldirCmd.description = 'generating ' + output.filePath
			qmldirCmd.highlight = 'codegen';
			qmldirCmd.sourceCode = function() {
				var f = new TextFile(output.filePath, TextFile.WriteOnly);
				try {
					var config = {
						moduleIdentifier: product.cutehmi.qmldir.moduleIdentifier,
						major: product.cutehmi.qmldir.major,
						minor: product.cutehmi.qmldir.minor,
						singletons: product.cutehmi.qmldir.singletons,
						output: output,
						outputSourceBase: product.installSourceBase,
						outputInstallDir: product.cutehmi.dirs.installDir + "/" + product.dedicatedInstallSubdir,
						inputs: inputs["cutehmi.qmldir.entity." + product.name],
						overridingInputs: undefined,
						inputsSourceBase: product.installSourceBase,
						inputsInstallDir: product.cutehmi.dirs.installDir + "/" + product.dedicatedInstallSubdir,
						excludedInputs: product.cutehmi.qmldir.exclude,
						filesMap: product.cutehmi.qmldir.filesMap,
						hasPlugin: product.type.contains("dynamiclibrary") && inputs["cutehmi.qmldir.qmlPlugin"] !== undefined,
						plugins: product.cutehmi.qmldir.plugins,
						className: product.cutehmi.qmldir.className,
						typeInfo: product.cutehmi.qmldir.typeInfo,
						designerSupported: product.cutehmi.qmldir.designerSupported,
						additionalEntries: product.cutehmi.qmldir.additionalEntries
					}
					Prepare.writeEntries(f, config)
				} finally {
					f.close()
				}
			}

			var gitignoreCmd = new JavaScriptCommand();
			gitignoreCmd.description = 'generating ' + product.sourceDirectory + '/.gitignore'
			gitignoreCmd.highlight = 'codegen';
			gitignoreCmd.sourceCode = function() {
				var f = new TextFile(product.sourceDirectory + "/.gitignore", TextFile.ReadWrite);
				try {
					Prepare.writeGitignore(f)
				} finally {
					f.close()
				}
			}

			if (product.cutehmi.qmldir.modifyGitignore)
				return [qmldirCmd, gitignoreCmd]
			else
				return [qmldirCmd]
		}

		Artifact {
			filePath: product.sourceDirectory + "/qmldir"
			fileTags: ["cutehmi.qmldir", "qmldir"]
		}
	}
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
