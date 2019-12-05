var FileInfo = require("qbs.FileInfo");

/**
  This function generates include guard for a given file path.
  @param referenceDirectory reference directory in respect of which a relative path shall be calculated (typically
  'project.sourceDirectory').
  @param filePath file path.
  @return include guard for a given file path.
  */
function includeGuard(referenceDirectory, filePath)
{
	return "H_" + FileInfo.relativePath(referenceDirectory, filePath).toUpperCase().replace(/_/g, '_u_').replace(/\.|\//g, '_')
}
