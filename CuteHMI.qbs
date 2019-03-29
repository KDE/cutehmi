import qbs

Project {
	property bool buildExamples: true

	property bool buildExtensions: true

	property bool buildTests: false

	property bool buildTools: true

	property bool staticExtensions: false

	qbsSearchPaths: ["qbs"]

	references: [
		"tools/tools.qbs",
		"extensions/extensions.qbs"
	]

	AutotestRunner {
		environment: {
			var env = base;
			env.push("QML2_IMPORT_PATH=" + qbs.installRoot + "/" + cutehmi.dirs.extensionInstallDirname);

			env.push("QBS_INSTALL_ROOT=" + qbs.installRoot);

			if (qbs.hostOS.contains("windows") && qbs.targetOS.contains("windows")) {
				var path = "";
				for (var i = 0; i < env.length; ++i) {
					if (env[i].startsWith("PATH=")) {
						path = env[i].substring(5);
						break;
					}
				}
				path = Qt.core.binPath + ";" + path;
				var arrayElem = "PATH=" + path;
				if (i < env.length)
					env[i] = arrayElem;
				else
					env.push(arrayElem);
			}

			if (qbs.hostOS.contains("darwin") && qbs.targetOS.contains("darwin")) {
				env.push("DYLD_FRAMEWORK_PATH=" + Qt.core.libPath);
				env.push("DYLD_LIBRARY_PATH=" + Qt.core.libPath);
			}

			return env;
		}

		Depends { name: "Qt.core" }

		Depends { name: "cutehmi.dirs" }
	}
}
