import qbs
import qbs.FileInfo
import qbs.File

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	name:  "android_" + extensionName

	condition: qbs.targetOS.contains("android")

	type: ["dynamiclibrary", "android.nativelibrary"]

	targetName: extensionName

	cutehmiType: "androidQMLPlugin"

	baseName: isNaN(extensionName.substr(extensionName.lastIndexOf(".", extensionName.length - 1) + 1)) ? extensionName : extensionName.substring(0, extensionName.lastIndexOf(".", extensionName.length - 1))

	files: {
		var namespaceRelativePath = baseName.toLowerCase().replace(/\./g, '/')

		var pathArray = [
			sourceDirectory,
			"src",
			namespaceRelativePath,
			"internal"
		]

		var internalDirPath = pathArray.join('/')

		var headerPath = internalDirPath + "/QMLPlugin.hpp"
		var sourcePath = internalDirPath + "/QMLPlugin.cpp"

		return [headerPath, sourcePath]
	}

	property string extensionName

	property string extensionRelativePath: FileInfo.relativePath(cutehmi.dirs.extensionsSourceDir, sourceDirectory)

	Group {
		name: "Android QML plugin"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.extensionInstallDirname + "/" + extensionRelativePath
	}

	Depends { name: extensionName }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "Qt.qml" }
}
