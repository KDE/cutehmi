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
