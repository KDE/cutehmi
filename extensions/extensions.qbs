import qbs.File

Project {
	minimumQbsVersion: "1.10"

	references: extensionsProbe.projectDirs

	/*
	  This probe performs a two-level deep search for project directories. It first scans current directory for its subdirectories.
	  If subdirectory contains a dot character ('.'), then it is considered to be a project directory with a major version number
	  after the dot. If subdirectory does not contain a dot character, then its own subdirectories are considered to be project
	  directories. This follows a typical layout for QML extensions. Project directories are stored in `projectDirs` property.
	  */
	Probe {
		id: extensionsProbe

		property pathList projectDirs: []

		configure: {
			var topDirs = File.directoryEntries(path, File.Dirs | File.NoDotAndDotDot)
			var result = []
			for (var i = 0; i < topDirs.length; i++)
				if (topDirs[i].indexOf('.') === -1) {
					var subDirs = File.directoryEntries(path + "/" +topDirs[i], File.Dirs | File.NoDotAndDotDot)
					for (var j = 0; j < subDirs.length; j++)
						result.push(topDirs[i] + "/" + subDirs[j])
				} else
					result.push(topDirs[i])
			projectDirs = result
		}
	}
}
