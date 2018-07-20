import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: ["dynamiclibrary"]

	cutehmiType: "module"

	cpp.defines: base.concat([baseName.toUpperCase() + "_BUILD", baseName.toUpperCase() + "_DYNAMIC"])

	baseName: name.substring(0, name.lastIndexOf("_", name.length - 1))

	major: Number(name.substr(name.lastIndexOf("_", name.length - 1) + 1))

	Depends { name: "cutehmi.metadata" }
	Depends { name: "cutehmi.dirs" }

	Export {
		property int reqMinor: minor

		Depends { name: "cpp" }
//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
		cpp.defines: [product.baseName.toUpperCase() + "_DYNAMIC", product.baseName.toUpperCase() + "_" + product.major + "_" + reqMinor]
		// Instead of somtehing like:
		// cpp.defines: [product.baseName.toUpperCase() + "_DYNAMIC", product.baseName.toUpperCase() + "_" + product.major + "_" + cutehmi.depends.reqMinor]
//</workaround>
		cpp.includePaths: [product.sourceDirectory + "/include"]

		cpp.libraryPaths: if (product.cpp.libraryPaths) importingProduct.cpp.libraryPaths.uniqueConcat(product.cpp.libraryPaths)
	}

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.moduleInstallDir
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
