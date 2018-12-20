import qbs

import cutehmi

cutehmi.Example {
	name: "SampleProject"

	vendor: "CuteHMI"

	friendlyName: "Sample Project"

	description: "Sample project."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "WTFNWPL"

	files: [
		"SampleProject.cutehmi.xml",
		"ServicesView.qml",
		"_Main.ui.qml",
	]

	Depends { name: "cutehmi_view" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
