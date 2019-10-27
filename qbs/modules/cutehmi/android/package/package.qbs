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

//(c)C: Copyright © 2019, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
