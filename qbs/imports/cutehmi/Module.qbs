import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: ["dynamiclibrary"]

	buildDefines: base.concat([baseName.toUpperCase() + "_BUILD", baseName.toUpperCase() + "_DYNAMIC"])

	property string vendor					///< Product vendor.

	property string friendlyName			///< Descriptive product name for ordinary humans.

	property string description				///< Product description.

	property string author					///< Author(s).

	property string copyright				///< Copyright holder(s).

	property string license					///< License(s).

	property string baseName: name.substring(0, name.lastIndexOf("_", name.length - 1))

	property int major: Number(name.substr(name.lastIndexOf("_", name.length - 1) + 1))

	property int minor: Number(String(version).split('.')[0])

	Depends { name: "cutehmi.metadata" }

	Depends { name: "cpp" }

	Export {
		Depends { name: "cpp" }
//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
		cpp.defines: [product.baseName.toUpperCase() + "_DYNAMIC",
			product.baseName.toUpperCase() + "_" + product.major + "_" + (importingProduct[product.name] && importingProduct[product.name].version ? String(importingProduct[product.name].version).split('.')[0] : product.minor)]
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
