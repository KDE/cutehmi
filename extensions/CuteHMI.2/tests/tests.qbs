import qbs

import "Test.qbs" as Test

Project {
	Test {
		testName: "test_logging"

		files: [
			"test_logging.cpp",
		]
	}

	Test {
		testName: "test_Exception"

		files: [
			"test_Exception.cpp",
		]

		Depends { name: "Qt.concurrent" }
	}

	Test {
		testName: "test_ExceptionMixin"

		files: [
			"test_ExceptionMixin.cpp",
		]

		Depends { name: "Qt.concurrent" }
	}

	Test {
		testName: "test_Dialog"

		files: [
			"test_Dialog.cpp",
		]
	}

	Test {
		testName: "test_Dialogist"

		files: [
			"test_Dialogist.cpp",
		]
	}

	Test {
		testName: "test_Singleton"

		files: [
			"test_Singleton.cpp",
		]
	}

	Test {
		testName: "test_QML"

		files: [
			"test_QML.cpp",
			"tst_Dialogist.qml",
		]

		Depends { name: "Qt.quick" }
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
