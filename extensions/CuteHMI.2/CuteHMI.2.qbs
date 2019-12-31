import qbs

import cutehmi

Project {
	name: "CuteHMI.2"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "CuteHMI"

		description: "Provides core functionality to other modules."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
         "README.md",
         "LICENSE",
         "ColorSet.qml",
         "Element.qml",
         "NumberDisplay.qml",
         "Palette.qml",
         "PropItem.qml",
         "include/cutehmi/Init.hpp",
         "include/cutehmi/Initializer.hpp",
         "include/cutehmi/InplaceError.hpp",
         "include/cutehmi/Message.hpp",
         "include/cutehmi/Messenger.hpp",
         "include/cutehmi/Notifier.hpp",
         "include/cutehmi/constants.hpp",
         "include/cutehmi/functions.hpp",
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
         "src/cutehmi/Message.cpp",
         "src/cutehmi/Messenger.cpp",
         "src/cutehmi/Notification.cpp",
         "src/cutehmi/NotificationListModel.cpp",
         "src/cutehmi/Notifier.cpp",
         "src/cutehmi/Singleton.cpp",
         "src/cutehmi/Worker.cpp",
         "src/cutehmi/internal/singleton.cpp",
         "src/cutehmi/logging.cpp",
         "src/cutehmi/internal/QMLPlugin.cpp",
         "src/cutehmi/internal/QMLPlugin.hpp",
     ]

		Depends { name: "Qt.core" }

		Depends { name: "Qt.qml" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['tests']

		Depends { name: "cutehmi.init" }

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }
		cutehmi.qmldir.singletons: ["Palette"]

		Depends { name: "cutehmi.qmltypes" }

		Export {
			Depends { name: "Qt.core" }

			Depends { name: "Qt.qml" }
		}
	}

	cutehmi.AndroidQMLPlugin {
		extensionName: parent.name
	}
}

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
