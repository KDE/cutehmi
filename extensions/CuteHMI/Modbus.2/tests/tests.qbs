import qbs

import "Test.qbs" as Test

Project {
	Test {
		testName: "test_logging"

		files: [
			"test_logging.cpp",
		]
	}
}
