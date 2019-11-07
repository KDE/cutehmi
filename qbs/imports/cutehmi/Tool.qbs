import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: project.buildApk ? "android.apk" : "application"

	cutehmiType: "tool"

	targetName: qbs.buildVariant.contains("debug") ? name + "_debug" : name

	condition: project.buildTools

	baseName: name

	cpp.includePaths: [cutehmi.dirs.externalIncludeDir]

	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	property stringList qmlImportPaths: [cutehmi.dirs.installDir + "/" + cutehmi.dirs.extensionInstallDirname]

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}

	Depends { name: "cutehmi.cpp" }

	Depends { name: "cutehmi.metadata" }

	Depends { name: "cutehmi.dirs" }

	Depends { name: "cutehmi.android.package"; condition: project.buildApk }
	Depends { name: "cutehmi.android.deployInstall"; condition: qbs.targetOS.contains("android") }

	Export {
		Depends { name: "cpp" }
	}

	Group {
		name: "Application"
		fileTagsFilter: "application"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.toolInstallDirname
	}
}

//(c)C: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>, Michal Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
