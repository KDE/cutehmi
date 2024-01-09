import qbs
import qbs.FileInfo

import "ProjectGroup.qbs" as ProjectGroup

/**
  Tool project.
  */
ProjectGroup {
	groupName: FileInfo.relativePath(project.sourceDirectory + "/" + project.toolsSubdir, groupSourceDirectory).replace(/\//g, '.')
}
