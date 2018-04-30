import qbs

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: "application"

	targetName: qbs.buildVariant.contains("debug") ? name + "_debug" : name

	baseName: name

	minor: Number(String(version).split('.')[0])

	micro: Number(String(version).split('.')[1])

	Depends { name: "cutehmi.metadata" }

	Properties {
		condition: qbs.targetOS.contains("linux")
		cpp.linkerFlags: "-rpath=$ORIGIN"
	}

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
