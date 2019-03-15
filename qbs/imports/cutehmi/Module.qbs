import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: project.staticModules ? ["staticlibrary"] : ["dynamiclibrary"]

	cutehmiType: "module"

	baseName: name.substring(0, name.lastIndexOf("_", name.length - 1))

	major: Number(name.substr(name.lastIndexOf("_", name.length - 1) + 1))

	cpp.defines: base.concat([baseName.toUpperCase() + "_BUILD"])

	cpp.includePaths: [product.sourceDirectory + "/include", cutehmi.dirs.externalIncludeDir]

	cpp.libraryPaths: [cutehmi.dirs.externalLibDir]

	Properties {
		condition: !project.staticModules
		cpp.defines: outer.concat([baseName.toUpperCase() + "_DYNAMIC"])
	}

	Depends { name: "cutehmi.metadata" }
	Depends { name: "cutehmi.dirs" }

	Export {
		property int reqMinor: minor

//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
		cpp.defines: [product.baseName.toUpperCase() + "_" + product.major + "_" + reqMinor]
		// Instead of somtehing like:
		// cpp.defines: [product.baseName.toUpperCase() + "_DYNAMIC", product.baseName.toUpperCase() + "_" + product.major + "_" + cutehmi.depends.reqMinor]
//</workaround>
		cpp.includePaths: [product.sourceDirectory + "/include"]

		cpp.libraryPaths: if (product.cpp.libraryPaths) product.cpp.libraryPaths

		Properties {
			condition: !project.staticModules
			cpp.defines: outer.concat([product.baseName.toUpperCase() + "_DYNAMIC"])
		}

		Depends { name: "cpp" }
	}

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: cutehmi.dirs.moduleInstallDirname
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
