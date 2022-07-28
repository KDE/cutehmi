import qbs.File

Project {
	references: toolsProbe.projectDirs

	/*
	  This probe simply scans current directory for subdirectories and stores the results in projectDirs property.
	  */
	Probe {
		id: toolsProbe

		property pathList projectDirs: []

		configure: {
			projectDirs = File.directoryEntries(path, File.Dirs | File.NoDotAndDotDot)
		}
	}
}
