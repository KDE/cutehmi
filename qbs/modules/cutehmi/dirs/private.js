var Environment = require("qbs.Environment");

function setupEnvironment()
{
	if (product.qbs.hostOS.contains("windows"))
		Environment.putEnv("PATH", product.cutehmi.dirs.externalLibDir + product.qbs.pathListSeparator + Environment.getEnv("PATH"))
	else
		Environment.putEnv("LD_LIBRARY_PATH", product.cutehmi.dirs.externalLibDir + product.qbs.pathListSeparator + Environment.getEnv("LD_LIBRARY_PATH"))

	Environment.putEnv("QML2_IMPORT_PATH", product.cutehmi.dirs.installDir + "/" + product.cutehmi.dirs.extensionInstallSubdir)

	Environment.putEnv("CUTEHMI_INSTALL_DIR", product.cutehmi.dirs.installDir)
	Environment.putEnv("CUTEHMI_TOOL_INSTALL_SUBDIR", product.cutehmi.dirs.toolInstallSubdir)
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
