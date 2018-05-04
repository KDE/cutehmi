import qbs

import cutehmi

cutehmi.Example {
	name: "SampleProject"

	vendor: "CuteHMI"

	friendlyName: "Sample Project"

	description: "Sample project."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "WTFPL"

	files: [
        "SampleProject.cutehmi.xml",
        "ServicesView.qml",
        "_Main.ui.qml",
    ]
}

