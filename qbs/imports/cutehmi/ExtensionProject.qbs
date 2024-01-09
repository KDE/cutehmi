import qbs
import qbs.FileInfo

import "ProjectGroup.qbs" as ProjectGroup

/**
  Extension project.
  */
ProjectGroup {
	groupName: FileInfo.relativePath(project.sourceDirectory + "/" + project.extensionsSubdir, groupSourceDirectory).replace(/\//g, '.')
}
