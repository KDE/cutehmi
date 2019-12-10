import qbs

import "Test.qbs" as Test

Project {
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
		testName: "test_Init"

		files: [
			"test_Init.cpp",
		]
	}

	Test {
		testName: "test_InplaceError"

		files: [
			"test_InplaceError.cpp",
		]
	}

	Test {
		testName: "test_ExtensionInitializer"

		files: [
			"test_ExtensionInitializer.cpp",
		]
	}

	Test {
		testName: "test_functions"

		files: [
			"test_functions.cpp",
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
		testName: "test_logging"

		files: [
			"test_logging.cpp",
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

	Test {
		testName: "test_Singleton"

		files: [
			"test_Singleton.cpp",
		]
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
