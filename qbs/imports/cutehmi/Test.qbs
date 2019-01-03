import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: ["application", "autotest"]

	name: testNamePrefix + "." + testName

	cutehmiType: "test"

	baseName: name

	condition: project.buildTests

	cpp.includePaths: [cutehmi.dirs.externalIncludeDir]

	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	property string testName

	property string testNamePrefix

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}

	Depends { name: "Qt.testlib" }
	Depends { name: "Qt.qmltest" }

	Depends { name: "cutehmi_test_1" }
	cutehmi_test_1.reqMinor: 0

	Depends { name: "cutehmi.dirs" }

	Group {
		name: "Application"
		fileTagsFilter: "application"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.testInstallDirname
	}

	cpp.defines: base.concat("QUICK_TEST_SOURCE_DIR=\"" + sourceDirectory + "\"")
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
