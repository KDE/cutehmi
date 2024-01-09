var File = require("qbs.File");

function validate(product) {
	var newProject = product.cutehmi.internal.clone.newProject
	var oldProject = product.cutehmi.internal.clone.oldProject
	var oldSourceDirectory = product.cutehmi.internal.clone.oldSourceDirectory
	var newSourceDirectory = product.cutehmi.internal.clone.newSourceDirectory
	var isExtension = oldSourceDirectory.startsWith(product.cutehmi.dirs.extensionsSourceDir)
	var isTool = oldSourceDirectory.startsWith(product.cutehmi.dirs.toolsSourceDir)

	if (!checkProjectName(oldProject))
		return false

	if (!checkProjectName(newProject))
		return false

	if (!isExtension && !isTool)
		throw "Project '" + oldProject + "' is currently not supported by 'cutehmi.clone' Qbs module."

	if (!projectPathExists(oldSourceDirectory))
		throw "Qbs module 'cutehmi.clone' could not find project '" + oldProject + "' directory under expected path '" + oldSourceDirectory + "'."

	if (projectPathExists(newSourceDirectory))
		throw "Qbs module 'cutehmi.clone' has found that directory '" + newSourceDirectory + "' already exists. Please remove it manually if you wish to clone the project."

	return true
}

function checkProjectName(projectName)
{
	var nameParts = projectName.split('.')

	if (nameParts.length < 2)
		throw "Project name should consist of at least of base name and major version number separated by a dot character (given name: '" + projectName + "')."

	if (!isInt(nameParts.slice(-1)))
		throw "Last part of the project name should be a major version number (given name: '" + projectName + "')."

	return true
}

function projectPathExists(projectPath)
{
	return File.exists(projectPath)
}

function extensionSubdir(productName)
{
	var nameParts = productName.split('.')
	var subdirPath = nameParts.slice(0, -2).join('/')
	var subdirName = nameParts.slice(-2).join('.')
	return subdirPath !== '' ? subdirPath + '/' + subdirName : subdirName
}

function toolSubdir(productName)
{
	return productName
}

function newSourceDirectory(product)
{
	var newProject = product.cutehmi.internal.clone.newProject
	var oldSourceDirectory = product.cutehmi.internal.clone.oldSourceDirectory
	var isExtension = oldSourceDirectory.startsWith(product.cutehmi.dirs.extensionsSourceDir)
	var isTool = oldSourceDirectory.startsWith(product.cutehmi.dirs.toolsSourceDir)

	if (isExtension)
		return product.cutehmi.dirs.extensionsSourceDir + "/" + extensionSubdir(newProject)
	else if (isTool)
		return product.cutehmi.dirs.toolsSourceDir + "/" + toolSubdir(newProject)
	else
		console.error("Unsupported product type")

	return undefined
}

// Source: https://stackoverflow.com/a/14794066/205955
function isInt(value) {
	var x = parseFloat(value);
	return !isNaN(value) && (x | 0) === x;
}
