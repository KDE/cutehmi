import qbs

import cutehmi

cutehmi.Example {
	name: "SimpleView"

	vendor: "CuteHMI"

	friendlyName: "Simple View"

	description: "Simple QML project."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "WTFNWPL"

	files: [
        "RectangularElement.qml",
        "_Main.qml",
    ]

	Depends { name: "cutehmi_view" }
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE, Version 1.
//(c)MP: DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//(c)MP: 0. You just DO WHAT THE FUCK YOU WANT TO.
//(c)MP: 1. NO FUCKING WARRANTY!
