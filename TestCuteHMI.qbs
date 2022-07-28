import qbs

Project {
	SubProject {
		filePath: "CuteHMI.qbs"

		Properties {
			buildTests: true
		}
	}
}
