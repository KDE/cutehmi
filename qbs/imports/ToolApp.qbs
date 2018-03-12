import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: "application"

	targetName: qbs.buildVariant.contains("debug") ? name + "_debug" : name

	Depends { name: "cpp" }

	Export {
		Depends { name: "cpp" }
	}

	Group {
		name: "Application"
		fileTagsFilter: "application"
		qbs.install: true
		qbs.installDir: "bin"
	}
}
