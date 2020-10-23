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

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
