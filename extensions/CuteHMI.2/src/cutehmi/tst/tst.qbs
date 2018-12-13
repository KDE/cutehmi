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
