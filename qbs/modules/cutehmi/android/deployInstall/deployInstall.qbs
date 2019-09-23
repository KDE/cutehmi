import qbs.FileInfo

/**
  This module installs QML files to the install root, so that qmlimportscanner is able to scan all imports from 
  qmlRootDir directory defined by android_support Qbs module.
  */
Module {
	property string installDir: cutehmi.dirs.extensionInstallDirname + "/" + FileInfo.relativePath(cutehmi.dirs.extensionsSourceDir, sourceDirectory)

	Depends { name: "cutehmi.dirs" }

	FileTagger {
		patterns: "*.js"
		fileTags: ["js"]
	}

	FileTagger {
		patterns: "*.qml"
		fileTags: ["qml"]
	}

	FileTagger {
		patterns: "*.qmltypes"
		fileTags: ["qmltypes"]
	}

	FileTagger {
		patterns: "qmldir"
		fileTags: ["qmldir"]
	}

	Group {
		name: "QML"
		fileTagsFilter: ["js", "qml", "qmldir", "qmltypes"]
		qbs.install: true
		qbs.installSourceBase: sourceDirectory
		qbs.installDir: installDir
	}
}
