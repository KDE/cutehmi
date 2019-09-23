import qbs.File
import qbs.Probes

/**
  This module sets all the necessary properties for tracking dependencies of CuteHMI extensions during APK building.
  */
Module {
	Android.sdk.packageName: packageName

	Qt.android_support.extraLibs: androidExtensionsProbe.extensionPaths

	Qt.android_support.extraPlugins: cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionInstallDirname

	Qt.android_support.qmlRootDir: cutehmi.dirs.installDir

	property string packageName: product.domain.split(".").reverse().join(".") + "." + product.name

	Depends { name: "Qt.android_support" }

	Depends { name: "Android.sdk" }

	Depends { name: "cutehmi.dirs" }

	Probe {
		id: androidExtensionsProbe

		property pathList searchPaths: [cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionInstallDirname]

		property string nameSuffix: ".so"

		property stringList extensionPaths: []

		configure: {
			var androidExtensionFilter = function(fileName) {
				return fileName.endsWith(nameSuffix);
			};

			var reducer = function(accumulator, searchPath) {
				var extensionFiles = File
					.directoryEntries(searchPath, File.Files)
					.filter(androidExtensionFilter)
					.map(function(fileName) {return searchPath + "/" + fileName});

				return accumulator.concat(extensionFiles);
			};

			extensionPaths = searchPaths.reduce(reducer, []);
		}
	}
}
