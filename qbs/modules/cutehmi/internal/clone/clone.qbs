import qbs
import qbs.File
import qbs.FileInfo
import qbs.TextFile

import "functions.js" as Functions

//<qbs-cutehmi.internal.clone-1.workaround target="Qbs" cause="missing">
import "cutehmi.skeleton.cpp.test_logging.js" as TestLogging
//</qbs-cutehmi.internal.clone-1.workaround>

/**
  Project cloner.
  */
Module {
	additionalProductTypes: ["cutehmi.internal.clone"]

	validate: Functions.validate(product)

	property string oldProject: product.cutehmi.clone.oldProject

	property string newProject: product.cutehmi.clone.newProject

	readonly property string oldSourceDirectory: project.groupSourceDirectory !== undefined ? project.groupSourceDirectory : product.sourceDirectory

	readonly property string newSourceDirectory: Functions.newSourceDirectory(product)

	readonly property string oldIncludesDir: oldSourceDirectory + "/" + product.cutehmi.conventions.functions.includesSubdir(oldProject)

	readonly property string oldSourcesDir: oldSourceDirectory + "/" + product.cutehmi.conventions.functions.sourcesSubdir(oldProject)

	readonly property string oldTestsDir: oldSourceDirectory + "/" + product.cutehmi.conventions.functions.testsSubdir(oldProject)

	readonly property string newIncludesDir: newSourceDirectory + "/" + product.cutehmi.conventions.functions.includesSubdir(newProject)

	readonly property string newSourcesDir: newSourceDirectory + "/" + product.cutehmi.conventions.functions.sourcesSubdir(newProject)

	readonly property string newTestsDir: newSourceDirectory + "/" + product.cutehmi.conventions.functions.testsSubdir(newProject)

	Depends { name: "cutehmi.conventions" }

	Depends { name: "cutehmi.dirs" }

	FileTagger {
		patterns: ["*"]
		fileTags: ["all"]
	}

	// Use this pool to prevent concurrent attempts to copy files, which are shared between products.
	JobLimit {
		jobPool: "cutehmi.internal.clone"
		jobCount: 1
	}

	Rule {
		readonly property bool valid: product.cutehmi.internal.clone.validate

		readonly property string oldProject: product.cutehmi.internal.clone.oldProject

		condition: valid && (project.groupName !== undefined ? project.groupName === oldProject
															 : project.name === oldProject)

		multiplex: true

		inputs: ["all", "qbs"]

		prepare: {
			var dirCmd = new JavaScriptCommand()
			dirCmd.description = "creating directory " + product.cutehmi.internal.clone.newSourceDirectory
			dirCmd.highlight = "codegen"
			dirCmd.jobPool = "cutehmi.internal.clone"
			dirCmd.newSourceDirectory = product.cutehmi.internal.clone.newSourceDirectory
			dirCmd.sourceCode = function() {
				File.makePath(newSourceDirectory)
			}

			var cloneCmd = new JavaScriptCommand()
			cloneCmd.description = "cloning project files from " + product.cutehmi.internal.clone.oldProject + " to " + product.cutehmi.internal.clone.newProject
			cloneCmd.highlight = "codegen"
			cloneCmd.jobPool = "cutehmi.internal.clone"
			cloneCmd.oldSourceDirectory = product.cutehmi.internal.clone.oldSourceDirectory
			cloneCmd.newSourceDirectory = product.cutehmi.internal.clone.newSourceDirectory
			cloneCmd.newIncludesDir = product.cutehmi.internal.clone.newIncludesDir
			cloneCmd.oldIncludesDir = product.cutehmi.internal.clone.oldIncludesDir
			cloneCmd.newSourcesDir = product.cutehmi.internal.clone.newSourcesDir
			cloneCmd.oldSourcesDir = product.cutehmi.internal.clone.oldSourcesDir
			cloneCmd.newTestsDir = product.cutehmi.internal.clone.newTestsDir
			cloneCmd.oldTestsDir = product.cutehmi.internal.clone.oldTestsDir
			cloneCmd.sourceCode = function() {
				var copiedQbsFiles = []
				var copiedAllFiles = []

				for (var index in inputs["qbs"]) {
					var sourcePath = inputs["qbs"][index].filePath
					if (inputs["qbs"][index].fileTags.includes("cutehmi.clone.exclude")) {
						console.log("file '" + sourcePath + "' is tagged as 'cutehmi.clone.exclude' and it won't be copied")
						continue
					}
					var targetPath = newSourceDirectory + "/" + FileInfo.relativePath(oldSourceDirectory, sourcePath)
					console.log("copying " + sourcePath + " to " + targetPath)
					File.copy(sourcePath, targetPath)
					copiedQbsFiles.push({"sourcePath": sourcePath,
											"sourceRelativePath": FileInfo.relativePath(product.sourceDirectory, sourcePath),
											"targetPath": targetPath,
											"targetRelativePath": FileInfo.relativePath(newSourceDirectory, targetPath),
										})
				}

				for (var index in inputs["all"]) {
					var sourcePath = inputs["all"][index].filePath
					if (inputs["all"][index].fileTags.includes("cutehmi.clone.exclude")) {
						console.log("file '" + sourcePath + "' is tagged as 'cutehmi.clone.exclude' and it won't be copied")
						continue
					}

					var targetPath
					if (sourcePath.startsWith(oldIncludesDir))
						targetPath = newIncludesDir + "/" + FileInfo.relativePath(oldIncludesDir, sourcePath)
					else if (sourcePath.startsWith(oldSourcesDir))
						targetPath = newSourcesDir + "/" + FileInfo.relativePath(oldSourcesDir, sourcePath)
					else if (sourcePath.startsWith(oldTestsDir))
						targetPath = newTestsDir + "/" + FileInfo.relativePath(oldTestsDir, sourcePath)
					else
						targetPath = newSourceDirectory + "/" + FileInfo.relativePath(oldSourceDirectory, sourcePath)

					console.log("copying " + sourcePath + " to " + targetPath)
					File.copy(sourcePath, targetPath)
					// Note that for subproducts "targetRelativePath" is not a path relative to product that contains the file,
					// but a path relative to the root group project.
					copiedAllFiles.push({"sourcePath": sourcePath,
											"sourceRelativePath": FileInfo.relativePath(product.sourceDirectory, sourcePath),
											"targetPath": targetPath,
											"targetRelativePath": FileInfo.relativePath(newSourceDirectory, targetPath),
										})
				}

				console.warn("modifying Qbs file(s) of project " + product.cutehmi.internal.clone.newProject)
				for (var qbsFileIndex in copiedQbsFiles) {
					var qbsFilePath = copiedQbsFiles[qbsFileIndex]["targetPath"]
					var qbsFile = new TextFile(qbsFilePath, TextFile.ReadOnly);
					try {
						var content = qbsFile.readAll()
					} finally {
						qbsFile.close()
					}

					for (var allFileIndex in copiedAllFiles) {
						var entry = copiedAllFiles[allFileIndex]
						// Target path relative to target Qbs file
						var qbsRelativeTargetPath = FileInfo.relativePath(FileInfo.path(qbsFilePath), entry["targetPath"])
						content = content.replace(entry["sourceRelativePath"], qbsRelativeTargetPath)
					}

					var qbsFile = new TextFile(qbsFilePath, TextFile.WriteOnly);
					try {
						qbsFile.write(content)
					} finally {
						qbsFile.close()
					}
				}

				//<qbs-cutehmi.internal.clone-1.workaround target="Qbs" cause="missing">
				TestLogging.process(copiedQbsFiles, copiedAllFiles)
				//</qbs-cutehmi.internal.clone-1.workaround>
			}

			return [dirCmd, cloneCmd]
		}

		outputFileTags: ["cutehmi.internal.clone"]
	}
}

//(c)C: Copyright © 2024, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
