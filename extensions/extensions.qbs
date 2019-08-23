import qbs.File

Project {
	minimumQbsVersion: "1.10"

	references: extensionsProbe.extensionDirs

	/*
	  This probe performs a recursive search for extension directories. It first scans current directory for its subdirectories.
	  If subdirectory contains a dot character ('.'), then it is considered to be an extension directory with a major version number
	  after the dot. If subdirectory does not contain a dot character, then it is recursively scanned for extension directories.
	  Extension directories are stored in `extensionDirs` property.
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
			function findExtensionDirs(rootPath, dir, result)
			{
				var dirs = File.directoryEntries(rootPath + "/" + dir, File.Dirs | File.NoDotAndDotDot)
				for (var i = 0; i < dirs.length; i++)
					if (dirs[i].indexOf('.') === -1)
						findExtensionDirs(rootPath, dir + dirs[i] + "/", result)	// Intrnally trailing slash has to be appended however.
					else
						result.push(dir + dirs[i])
			}

			var result = []
			findExtensionDirs(path, "", result)
			extensionDirs = result
		}
	}
}
