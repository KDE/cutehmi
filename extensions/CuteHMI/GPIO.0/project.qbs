import qbs

import cutehmi

Project {
	name: "CuteHMI.GPIO.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		cutehmi.product.enabled: cutehmi.libs.libgpiod.found

		friendlyName: "General-purpose Input/Output"

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		description: "An extension built on top of 'libgpiod' library to deal with GPIO chips."

		files: [
		 "README.md",
		 "include/cutehmi/gpio/Chip.hpp",
		 "include/cutehmi/gpio/ChipEnumerator.hpp",
		 "include/cutehmi/gpio/Line.hpp",
		 "include/cutehmi/gpio/LineConfig.hpp",
		 "include/cutehmi/gpio/internal/LineEventMonitorThread.hpp",
		 "include/cutehmi/gpio/internal/common.hpp",
		 "include/cutehmi/gpio/internal/platform.hpp",
		 "include/cutehmi/gpio/logging.hpp",
		 "include/cutehmi/gpio/metadata.hpp",
		 "src/cutehmi/gpio/Chip.cpp",
		 "src/cutehmi/gpio/ChipEnumerator.cpp",
		 "src/cutehmi/gpio/Line.cpp",
		 "src/cutehmi/gpio/LineConfig.cpp",
		 "src/cutehmi/gpio/internal/LineEventMonitorThread.cpp",
		 "src/cutehmi/gpio/internal/QMLPlugin.cpp",
		 "src/cutehmi/gpio/internal/QMLPlugin.hpp",
		 "src/cutehmi/gpio/logging.cpp",
	 ]

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.libs.libgpiod" }

//		Depends { name: "cutehmi.doxygen" }
//		cutehmi.doxygen.warnIfUndocumented: false
//		cutehmi.doxygen.useDoxyqml: true
//		cutehmi.doxygen.exclude: ['tests']

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltyperegistrar" }

		Export {
			Depends { name: "cutehmi.libs.libgpiod" }

			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
