import qbs

import cutehmi

import "Test.qbs" as Test

Project {
	Test {
		testName: "test_cutehmi_daemon"

		files: [
			"test_cutehmi_daemon.cpp",
		]
	}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
