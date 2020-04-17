import qbs
import qbs.FileInfo

import "Extension.qbs" as Extension

/**
  Puppet extension product.
  */
Extension {
	name: "puppet." + originalExtension

	installSourceBase: sourceDirectory + "/" + cutehmi.dirs.puppetSourceSubdir

	dedicatedInstallSubdir: cutehmi.dirs.puppetsInstallSubdir + "/" + FileInfo.relativePath(cutehmi.dirs.extensionsSourceDir, sourceDirectory)

	property string originalExtension

	Depends { name: "cutehmi.metadata" }
	cutehmi.metadata.artifacts: false

	Depends { name: "cutehmi.qmldir" }
	cutehmi.qmldir.puppet: true
	// PuppetExtension normally should not have its own binaries. The only reason it would want its own binaries is for workarounds.
	// Because of workarounds plugins array is always concatenated with that of original extension, so if there are no workarounds
	// it must be explicitly specified as empty. Otherwise a default plugin entry would act as a supposed workaround.
	// Note: plugin entry in 'qmldir' of a puppet extension will be created by 'cutehmi.qmldir' only if original extensions has a
	// plugin.
	//<qbs-imports-cutehmi-4.workaround target="QtCreator_Windows" cause="missing">
	Properties {
		condition: qbs.targetOS.contains("windows")
		cutehmi.qmldir.plugins: [{
				name: "CuteHMI.Workarounds.PuppetBootloader.0",
				path: FileInfo.relativePath(cutehmi.dirs.installDir + "/" + dedicatedInstallSubdir,
											cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionsInstallSubdir)
			}]
	}
	//</qbs-imports-cutehmi-4.workaround>
	cutehmi.qmldir.plugins: []

	Depends { name: originalExtension }
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
