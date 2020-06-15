import qbs.File

Project {
	minimumQbsVersion: "1.10"

	references: extensionsProbe.extensionDirs

	/*
	  This probe performs a recursive search for extension directories. It first scans current directory for its subdirectories.
	  Each directory, which contains `project.qbs` file or a `.qbs` file with the same base name as name of the directory, where it
	  resides is considered to be an extension directory. If subdirectory does not contain any of these files, then it is
	  recursively scanned for extension directories. Extension directories are stored in `extensionDirs` property.
	 */
	Probe {
		id: extensionsProbe

		property pathList extensionDirs: []

		configure: {
			/*
			  Recursive function that searches for extension directories.
			  @param rootPath root path, where the search should start.
			  @param dir directory relative to root path, which is going to be scanned for extension directories. Do not add
				trailing "/" (slash) upon external call.
			  @param result array containing list of extension directories.
			 */
			function findExtensionDirs(rootPath, dir, result) {
				var dirs = File.directoryEntries(rootPath + "/" + dir, File.Dirs | File.NoDotAndDotDot)
				for (var i = 0; i < dirs.length; i++) {
					var qbsFileDir = rootPath + "/" + dir + dirs[i] + "/"
					if (File.exists(qbsFileDir + "project.qbs") || File.exists(qbsFileDir + dirs[i] + ".qbs"))
						result.push(dir + dirs[i])
					else
						findExtensionDirs(rootPath, dir + dirs[i] + "/", result)	// Internally trailing slash has to be appended however.
				}
			}

			var result = []
			findExtensionDirs(path, "", result)
			extensionDirs = result
		}
	}
}
