import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: "application"

	targetName: qbs.buildVariant.contains("debug") ? name + "_debug" : name

	baseName: name

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}

	Depends { name: "cutehmi.metadata" }
	Depends { name: "cutehmi.dirs" }

	Depends { name: "cpp" }

	Export {
		Depends { name: "cpp" }
	}

	Group {
		name: "Application"
		fileTagsFilter: "application"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.toolInstallDir
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
