import qbs

import "CommonProduct.qbs" as CommonProduct

/**
  Test product.
  */
CommonProduct {
	type: project.buildBinaries ? ["application", "autotest"] : []

	name: testNamePrefix + "." + testName

	cutehmiType: "test"

	baseName: name

	//<qbs-imports-cutehmi-2.workaround target="Qbs" cause="bug">
	// Even tho' 'type' property can conditionaly specify "autotest", when condition involves complex evaluation of module
	// parameters such as 'cutehmi.product.enabled' (probably causing some re-evaluation) AutotestRunner will not conform to the
	// final results, but rather stick to some initial results (branch that specifies "autotest"). Using 'condition' seems to
	// resolve the issue. No product should depend on a test product, so no product should be affected by
	// "qbs-imports-cutehmi-1.workaround".
	condition: project.buildTests && cutehmi.product.enabled
	//</qbs-imports-cutehmi-2.workaround>

	property string testedProduct

	property string testName

	property string testNamePrefix: testedProduct

	Depends { name: "cpp" }
	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}
	cpp.defines: base.concat("QUICK_TEST_SOURCE_DIR=\"" + sourceDirectory + "\"")
	cpp.includePaths: [
		cutehmi.dirs.externalIncludeDir,
		product.sourceDirectory + "/" + cutehmi.conventions.functions.includesSubdir(product.name)
	]
	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	Depends { name: "autotest" }
	autotest.arguments: ["-o", name + ".xunit.xml,xunitxml"]
	autotest.allowFailure: true

	Depends { name: "Qt.testlib" }

	Depends { name: "Qt.qmltest" }

	Depends { name: "cutehmi.cpp" }

	Depends { name: "cutehmi.dirs" }

	Group {
		name: "Application"
		fileTagsFilter: "application"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.testsInstallSubdir
	}

	Group {
		name: "Translations"
		fileTagsFilter: ["qm"]
		qbs.install: true
		qbs.installDir: cutehmi.dirs.translationsInstallSubdir
	}
}

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
