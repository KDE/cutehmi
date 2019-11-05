function setupEnvironment()
{
	if (product.qbs.targetOS.contains("windows"))
		Environment.putEnv("PATH", product.cutehmi.dirs.externalLibDir + product.qbs.pathListSeparator + Environment.getEnv("PATH"))
	else
		Environment.putEnv("LD_LIBRARY_PATH", product.cutehmi.dirs.externalLibDir + product.qbs.pathListSeparator + Environment.getEnv("LD_LIBRARY_PATH"))

	Environment.putEnv("QML2_IMPORT_PATH", product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallDirname)

	Environment.putEnv("CUTEHMI_INSTALL_DIR", product.cutehmi.dirs.installDir)
}
