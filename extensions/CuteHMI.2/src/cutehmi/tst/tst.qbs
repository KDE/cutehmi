import qbs

import cutehmi

import "TestCase.qbs" as TestCase

Project {
	TestCase {
		name: "logging"
		files: [
			"tst_logging.cpp",
		]
	}

	TestCase {
		name: "Exception"
		files: [
			"tst_Exception.cpp"
		]

		Depends { name: "Qt.concurrent" }
	}

	TestCase {
		name: "ExceptionMixin"
		files: [
			"tst_ExceptionMixin.cpp"
		]

		Depends { name: "Qt.concurrent" }
	}

	TestCase {
		name: "Prompt"
		files: [
			"tst_Prompt.cpp",
		]
	}

	TestCase {
		name: "PopupBridge"
		files: [
			"tst_PopupBridge.cpp",
		]
	}

	TestCase {
		name: "PopupBridgeQML"

		files: [
         "tst_PopupBridge.qml",
         "tst_PopupBridgeQML.cpp",
     ]
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
