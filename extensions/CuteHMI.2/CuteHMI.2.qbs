import qbs

import cutehmi

Project {
	name: "CuteHMI.2"

	cutehmi.Extension {
		name: "CuteHMI.2"

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		friendlyName: "CuteHMI"

		description: "Provides core functionality to other modules."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "Mozilla Public License, v. 2.0"

		files: [
         "README.md",
         "LICENSE",
         "ColorSet.qml",
         "Element.qml",
         "NumberDisplay.qml",
         "Palette.qml",
         "PropItem.qml",
         "include/cutehmi/Dialog.hpp",
         "include/cutehmi/Dialogist.hpp",
         "include/cutehmi/Notifier.hpp",
         "include/cutehmi/wrappers.hpp",
         "qmldir",
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
         "src/cutehmi/Dialog.cpp",
         "src/cutehmi/Dialogist.cpp",
         "src/cutehmi/Error.cpp",
         "src/cutehmi/ErrorException.cpp",
         "src/cutehmi/ErrorInfo.cpp",
         "src/cutehmi/Exception.cpp",
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

		Export {
			Depends { name: "Qt.core" }
			Depends { name: "Qt.qml" }
		}
	}

	SubProject {
		filePath: "tests/tests.qbs"

		Properties {
			condition: parent.buildTests
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
