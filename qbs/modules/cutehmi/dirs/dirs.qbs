import qbs

Module {
	property string moduleInstallDir: "bin"
	property string toolInstallDir: "bin"
	property string qmlExtensionInstallDir: "QML"
	property string qmlPluginInstallDir: "plugins"

	property string externalDeployDir: project.sourceDirectory + "/external/deploy"
	property string externalLibDir: externalDeployDir + "/lib"
	property string externalIncludeDir: externalDeployDir + "/include"

	setupRunEnvironment: {
        if (qbs.targetOS.contains("windows"))
            Environment.putEnv("PATH", externalLibDir + qbs.pathListSeparator + Environment.getEnv("PATH"))
        else
            Environment.putEnv("LD_LIBRARY_PATH", externalLibDir + qbs.pathListSeparator + Environment.getEnv("LD_LIBRARY_PATH"))
	}
}
