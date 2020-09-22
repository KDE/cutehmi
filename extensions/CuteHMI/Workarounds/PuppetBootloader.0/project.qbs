import qbs

import cutehmi

//<qbs-imports-cutehmi-4.workaround target="QtCreator_Windows" cause="missing">

Project {
	name: "CuteHMI.Workarounds.PuppetBootloader.0"

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Puppet Bootloader"

		description: "Hackish initialization plugin intended to be used by Qt Creator in Design mode."

		files: [
			"LICENSE.LGPL3",
			"LICENSE.MIT",
			"src/cutehmi/workarounds/puppetbootloader/internal/Init.cpp",
			"src/cutehmi/workarounds/puppetbootloader/internal/Init.hpp",
			"src/cutehmi/workarounds/puppetbootloader/internal/QMLPlugin.cpp",
			"src/cutehmi/workarounds/puppetbootloader/internal/QMLPlugin.hpp",
		]

		Group {
			name: "Windows"
			condition: qbs.targetOS.contains("windows")
			files: [
				"src/cutehmi/workarounds/puppetbootloader/internal/Init_win.cpp",
			]
		}

		Group {
			name: "Generic"
			condition: !qbs.targetOS.contains("windows")
			files: [
				"src/cutehmi/workarounds/puppetbootloader/internal/Init_generic.cpp",
			]
		}


		Depends { name: "Qt.core" }

		Depends { name: "Qt.qml" }
	}
}

//</qbs-imports-cutehmi-4.workaround>

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
