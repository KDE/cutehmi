import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: "dynamiclibrary"

	property string pluginName: name.substring(0, name.lastIndexOf("_", name.length - 1))

	property string pluginMajor: name.substr(name.lastIndexOf("_", name.length - 1) + 1)

	buildDefines: base.concat([pluginName.toUpperCase() + "_BUILD", pluginName.toUpperCase() + "_DYNAMIC"])

	Depends { name: "cpp" }

	Export {
		Depends { name: "cpp" }
		cpp.defines: [product.pluginName.toUpperCase() + "_DYNAMIC"]
		cpp.includePaths: [product.sourceDirectory + "/include"]
	}

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: "bin"
	}
}
