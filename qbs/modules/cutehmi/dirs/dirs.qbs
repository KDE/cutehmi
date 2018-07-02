import qbs

Module {
	property string moduleInstallDir: "bin"
	property string toolInstallDir: "bin"
	property string qmlExtensionInstallDir: "QML"
	property string qmlPluginInstallDir: "plugins"

	property string externalLibDir: project.sourceDirectory + "/external/deploy"
}
