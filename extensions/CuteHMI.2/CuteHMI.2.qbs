import qbs

import cutehmi

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
        "ColorSet.qml",
        "Element.qml",
        "LICENSE",
        "NumberDisplay.qml",
        "Palette.qml",
        "PropItem.qml",
        "README.md",
        "include/cutehmi/CuteHMI.hpp",
        "include/cutehmi/Error.hpp",
        "include/cutehmi/ErrorException.hpp",
        "include/cutehmi/ErrorInfo.hpp",
        "include/cutehmi/Exception.hpp",
        "include/cutehmi/ExceptionMixin.hpp",
        "include/cutehmi/IMetadataPlugin.hpp",
        "include/cutehmi/IProjectBackend.hpp",
        "include/cutehmi/IProjectPlugin.hpp",
        "include/cutehmi/MPtr.hpp",
        "include/cutehmi/NonCopyable.hpp",
        "include/cutehmi/NonMovable.hpp",
        "include/cutehmi/Notification.hpp",
        "include/cutehmi/NotificationListModel.hpp",
        "include/cutehmi/NotificationManager.hpp",
        "include/cutehmi/PopupBridge.hpp",
        "include/cutehmi/Prompt.hpp",
        "include/cutehmi/Singleton.hpp",
        "include/cutehmi/Worker.hpp",
		"include/cutehmi/internal/common.hpp",
        "include/cutehmi/internal/platform.hpp",
        "include/cutehmi/logging.hpp",
        "include/cutehmi/loggingMacros.hpp",
        "include/cutehmi/metadata.hpp",
        "qmldir",
        "src/cutehmi/CuteHMI.cpp",
        "src/cutehmi/Error.cpp",
        "src/cutehmi/ErrorException.cpp",
        "src/cutehmi/ErrorInfo.cpp",
        "src/cutehmi/Exception.cpp",
        "src/cutehmi/Notification.cpp",
        "src/cutehmi/NotificationListModel.cpp",
        "src/cutehmi/NotificationManager.cpp",
        "src/cutehmi/PopupBridge.cpp",
        "src/cutehmi/Prompt.cpp",
        "src/cutehmi/Worker.cpp",
        "src/cutehmi/logging.cpp",
		"src/cutehmi/internal/QMLPlugin.cpp",
		"src/cutehmi/internal/QMLPlugin.hpp",
    ]

	Depends { name: "Qt.core" }
	Depends { name: "Qt.qml" }

	Depends { name: "cutehmi.doxygen" }
	cutehmi.doxygen.warnIfUndocumented: false

	Export {
		Depends { name: "Qt.core" }
		Depends { name: "Qt.qml" }
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
