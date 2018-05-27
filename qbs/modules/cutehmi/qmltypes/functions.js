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
