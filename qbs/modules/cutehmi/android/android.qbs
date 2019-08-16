import qbs.File
import qbs.Probes

Module {
	Android.sdk.packageName: packageName

	Qt.android_support.extraLibs: androidExtensionsProbe.extensionPaths

	property string packageName

	Depends { name: "Qt.android_support" }

	Depends { name: "Android.sdk" }

	Depends { name: "cutehmi.dirs" }

	FileTagger {
		patterns: "*.qml"
		fileTags: ["android.assets"]
	}

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
