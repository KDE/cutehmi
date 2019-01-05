import qbs.File

Project {
	minimumQbsVersion: "1.6"

	references: examplesProbe.projectDirs

	/*
	  This probe simply scans current directory for subdirectories and stores the results in projectDirs property.
	  */
	Probe {
		id: examplesProbe

		property pathList projectDirs: []

		configure: {
			projectDirs = File.directoryEntries(path, File.Dirs | File.NoDotAndDotDot)
		}
	}
}
