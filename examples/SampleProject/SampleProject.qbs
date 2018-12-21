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
//(c)MP: This Source Code Form is subject to the terms of the DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE, Version 1.
//(c)MP: DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//(c)MP: 0. You just DO WHAT THE FUCK YOU WANT TO.
//(c)MP: 1. NO FUCKING WARRANTY!
