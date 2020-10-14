import qbs 1.0
import qbs.Probes
import qbs.FileInfo

/**
  Library for GPIO support.
  */
Module {
	property bool found: libraryProbe.found && headerProbe.found

	property bool available: found

	property string libraryPath: libraryProbe.filePath

	property string includePath: headerProbe.path

	Probes.PathProbe {
		id: libraryProbe

		names: ["libgpiod"]
		nameSuffixes: [".so"]
		//<qbs-cutehmi.libs.libgpiod-1.workaround target="Linux_distributions" cause="stale">
		// Unless packages are upgraded deprecated features such as "pathPrefixes" have to be used.
		pathPrefixes: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
							.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
							.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
							.concat([cutehmi.dirs.externalLibDir])
		// Instead of:
		//	searchPaths: cpp.libraryPaths.concat(cpp.compilerLibraryPaths ? cpp.compilerLibraryPaths : [])
		//					.concat(cpp.systemRunPaths ? cpp.systemRunPaths : [])
		//					.concat(cpp.distributionLibraryPaths ? cpp.distributionLibraryPaths : [])
		//					.concat([cutehmi.dirs.externalLibDir])
		//</qbs-cutehmi.libs.libgpiod-1.workaround>
	}

	Probes.PathProbe {
		id: headerProbe

		names: ["gpiod.h"]
		//<qbs-cutehmi.libs.libgpiod-1.workaround target="Linux_distributions" cause="stale">
		// Unless packages are upgraded deprecated features such as "pathPrefixes" have to be used.
		pathPrefixes: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
							.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
							.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
							.concat([cutehmi.dirs.externalIncludeDir])
		// Instead of:
		//	searchPaths: cpp.includePaths.concat(cpp.compilerIncludePaths ? cpp.compilerIncludePaths : [])
		//					.concat(cpp.systemIncludePaths ? cpp.systemIncludePaths : [])
		//					.concat(cpp.distributionIncludePaths ? cpp.distributionIncludePaths : [])
		//					.concat([cutehmi.dirs.externalIncludeDir])
		//</qbs-cutehmi.libs.libgpiod-1.workaround>
	}

	Depends { name: "cpp" }

	Depends { name: "cutehmi.dirs" }
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
