import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: ["dynamiclibrary"]

	buildDefines: base.concat([baseName.toUpperCase() + "_BUILD", baseName.toUpperCase() + "_DYNAMIC"])

	baseName: name.substring(0, name.lastIndexOf("_", name.length - 1))

	major: Number(name.substr(name.lastIndexOf("_", name.length - 1) + 1))

	Depends { name: "cutehmi.metadata" }

	Depends { name: "cpp" }

	Export {
		property int reqMinor: minor

		Depends { name: "cpp" }
//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
		cpp.defines: [product.baseName.toUpperCase() + "_DYNAMIC", product.baseName.toUpperCase() + "_" + product.major + "_" + reqMinor]
		// Instead of somtehing like:
		// cpp.defines: [product.baseName.toUpperCase() + "_DYNAMIC", product.baseName.toUpperCase() + "_" + product.major + "_" + cutehmi.depends.reqMinor]
//</workaround>
		cpp.includePaths: [product.sourceDirectory + "/include"]
	}

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: "bin"
	}
}
