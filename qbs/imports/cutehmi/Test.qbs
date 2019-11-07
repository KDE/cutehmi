import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: ["application", "autotest"]

	name: testNamePrefix + "." + testName

	cutehmiType: "test"

	baseName: name

	condition: project.buildTests

	property string testName

	property string testNamePrefix

	Depends { name: "cpp" }
	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}
	cpp.defines: base.concat("QUICK_TEST_SOURCE_DIR=\"" + sourceDirectory + "\"")
	cpp.includePaths: [cutehmi.dirs.externalIncludeDir]
	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	Depends { name: "Qt.testlib" }

	Depends { name: "Qt.qmltest" }

	Depends { name: "cutehmi.cpp" }

	Depends { name: "cutehmi.dirs" }

	Group {
		name: "Application"
		fileTagsFilter: "application"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.testInstallDirname
	}
}

//(c)C: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
