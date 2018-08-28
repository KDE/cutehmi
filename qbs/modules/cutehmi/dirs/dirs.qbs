import qbs

Module {
	property string moduleInstallDirname: "bin"
	property string toolInstallDirname: "bin"
	property string qmlExtensionInstallDirname: "QML"
	property string qmlPluginInstallDirname: "plugins"
	property string qmlSourceDir: project.sourceDirectory + "/QML"

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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
