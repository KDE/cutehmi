import qbs

import cutehmi

Project {
	name: "CuteHMI.Workarounds.Qt.labs.settings.1"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Qt.labs.settings Workaround"

		description: "Provides Qt.labs.settings components with an addition of essential functions missing in original implementation."

		files: [
         "GPL2.LICENSE",
         "GPL3.LICENSE",
         "LGPL3.LICENSE",
         "LICENSE",
         "README.md",
         "include/cutehmi/workarounds/qt/labs/settings/internal/common.hpp",
         "include/cutehmi/workarounds/qt/labs/settings/internal/platform.hpp",
         "include/cutehmi/workarounds/qt/labs/settings/logging.hpp",
         "include/cutehmi/workarounds/qt/labs/settings/metadata.hpp",
         "src/cutehmi/workarounds/qt/labs/settings/internal/QMLPlugin.cpp",
         "src/cutehmi/workarounds/qt/labs/settings/internal/QMLPlugin.hpp",
         "src/cutehmi/workarounds/qt/labs/settings/internal/qqmlsettings.cpp",
         "src/cutehmi/workarounds/qt/labs/settings/internal/qqmlsettings_p.h",
         "src/cutehmi/workarounds/qt/labs/settings/logging.cpp",
     ]

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltyperegistrar" }
		cutehmi.qmltyperegistrar.includePaths: cutehmi.conventions.sourceDir + "/internal"

		Depends { name: "CuteHMI.2" }

		Depends { name: "Qt.core" }

		Depends { name: "Qt.qml" }

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR GPL-2.0-or-later
//(c)C: CuteHMI.Workarounds.Qt.labs.settings.1 extension is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version approved by the KDE Free Qt Foundation.
//(c)C: This file is a part of CuteHMI.Workarounds.Qt.labs.settings.1 extension.
//(c)C: Additionally, this file is licensed under terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version approved by the KDE Free Qt Foundation.
//(c)C: CuteHMI.Workarounds.Qt.labs.settings.1 extension is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or GNU General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.Workarounds.Qt.labs.settings.1 extension. If not, see <https://www.gnu.org/licenses/>.
//(c)C: You should have received a copy of the GNU General Public License along with CuteHMI.Workarounds.Qt.labs.settings.1 extension. If not, see <https://www.gnu.org/licenses/>.
