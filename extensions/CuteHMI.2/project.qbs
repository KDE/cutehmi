import qbs

import cutehmi

Project {
	name: "CuteHMI.2"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "CuteHMI"

		description: "Provides core functionality to other modules."

		i18n: true

		files: [
         "README.md",
         "LICENSE.MIT",
         "LICENSE.LGPL3",
         "include/cutehmi/Init.hpp",
         "include/cutehmi/Initializer.hpp",
         "include/cutehmi/InplaceError.hpp",
         "include/cutehmi/Internationalizer.hpp",
         "include/cutehmi/Message.hpp",
         "include/cutehmi/Messenger.hpp",
         "include/cutehmi/Notifier.hpp",
         "include/cutehmi/constants.hpp",
         "include/cutehmi/functions.hpp",
         "include/cutehmi/internal/LoggingCategoryCheck.hpp",
         "include/cutehmi/macros.hpp",
         "include/cutehmi/wrappers.hpp",
         "include/cutehmi/Error.hpp",
         "include/cutehmi/ErrorException.hpp",
         "include/cutehmi/ErrorInfo.hpp",
         "include/cutehmi/Exception.hpp",
         "include/cutehmi/ExceptionMixin.hpp",
         "include/cutehmi/MPtr.hpp",
         "include/cutehmi/NonCopyable.hpp",
         "include/cutehmi/NonMovable.hpp",
         "include/cutehmi/Notification.hpp",
         "include/cutehmi/NotificationListModel.hpp",
         "include/cutehmi/Singleton.hpp",
         "include/cutehmi/Worker.hpp",
         "include/cutehmi/internal/common.hpp",
         "include/cutehmi/internal/platform.hpp",
         "include/cutehmi/internal/singleton.hpp",
         "include/cutehmi/logging.hpp",
         "include/cutehmi/loggingMacros.hpp",
         "include/cutehmi/metadata.hpp",
         "src/cutehmi/Error.cpp",
         "src/cutehmi/ErrorException.cpp",
         "src/cutehmi/ErrorInfo.cpp",
         "src/cutehmi/Exception.cpp",
         "src/cutehmi/Init.cpp",
         "src/cutehmi/InplaceError.cpp",
         "src/cutehmi/Internationalizer.cpp",
         "src/cutehmi/Message.cpp",
         "src/cutehmi/Messenger.cpp",
         "src/cutehmi/Notification.cpp",
         "src/cutehmi/NotificationListModel.cpp",
         "src/cutehmi/Notifier.cpp",
         "src/cutehmi/Singleton.cpp",
         "src/cutehmi/Worker.cpp",
         "src/cutehmi/functions.cpp",
         "src/cutehmi/internal/singleton.cpp",
         "src/cutehmi/logging.cpp",
         "src/cutehmi/internal/QMLPlugin.cpp",
         "src/cutehmi/internal/QMLPlugin.hpp",
     ]

		Depends { name: "Qt.core" }

		Depends { name: "Qt.qml" }

		cutehmi.dirs.artifacts: true

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'tests']

		Depends { name: "cutehmi.init" }

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltyperegistrar" }

		Export {
			Depends { name: "Qt.core" }

			Depends { name: "Qt.qml" }
		}
	}

	cutehmi.AndroidQMLPlugin {
		extensionName: parent.name
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
