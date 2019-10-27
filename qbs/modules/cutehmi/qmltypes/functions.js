function collectLibraryPaths(dependencies, recursive)
{
	var result = []
	for (i in dependencies) {
		if ("cpp" in dependencies[i]) {
			for (j in dependencies[i].cpp.libraryPaths) {
				var libraryPath = dependencies[i].cpp.libraryPaths[j]
				if (result.indexOf(libraryPath) === -1)
					result.push(libraryPath)
			}
			if (recursive) {
				// Recursive run for dependencies that were not exported.
				var unexportedLibraryPaths = collectLibraryPaths(dependencies[i].dependencies)
				for (j in unexportedLibraryPaths) {
					libraryPath = unexportedLibraryPaths[j]
					if (result.indexOf(libraryPath) === -1)
						result.push(libraryPath)
				}
			}
		}
	}
	return result
}

//(c)C: Copyright © 2018-2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
