import qbs
import qbs.FileInfo

import "CommonProduct.qbs" as CommonProduct

CommonProduct {
	type: "dynamiclibrary"

	baseName: name.substring(0, name.lastIndexOf("_", name.length - 1))

	major: Number(name.substr(name.lastIndexOf("_", name.length - 1) + 1))

	minor: Number(String(version).split('.')[0])

	property string installDir: FileInfo.relativePath(path + "/../../..", sourceDirectory)

	Depends { name: "cutehmi.metadata" }

	Properties {
		condition: qbs.targetOS.contains("linux")
		targetName: name
	}

	FileTagger {
		patterns: "*.qml"
		fileTags: ["qml"]
	}

	FileTagger {
		patterns: "*.js"
		fileTags: ["js"]
	}

	FileTagger {
		patterns: "qmldir"
		fileTags: ["qmldir"]
	}

	FileTagger {
		patterns: "plugins.qmltypes"
		fileTags: ["qmltypes"]
	}

	FileTagger {
		patterns: "*.metainfo"
		fileTags: ["metainfo"]
	}

	Depends { name: "cpp" }

	Group {
		name: "Library"
		fileTagsFilter: "dynamiclibrary"
		qbs.install: true
		qbs.installDir: installDir + "/plugins"
	}

	Group {
		name: "QML"
		fileTagsFilter: ["qml", "js", "qmldir", "qmltypes", "metainfo"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}
}
