Project {
	qbsSearchPaths: ["qbs"]

	SubProject {
		filePath: "modules/modules.qbs"
	}

	SubProject {
		filePath: "tools/tools.qbs"
	}

	SubProject {
		filePath: "QML/QML.qbs"
	}

	SubProject {
		filePath: "examples/examples.qbs"
	}
}
