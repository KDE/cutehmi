var Xml = require("qbs.Xml");
var Utilities = require("qbs.Utilities");
var File = require("qbs.File");
var FileInfo = require("qbs.FileInfo");
var TextFile = require("qbs.TextFile");

var guidCounter = 0

var idHashTable = {}

var qtRuntimeProductMock = {
	"name": "/QtRuntime/",	// Deliberately picking impossible product name.
	"friendlyName": "Qt Runtime",
	"description": "Qt Runtime.",
	"dependencies": [],
}

function createGuid() {
	var dateHex = Date.now().toString(16)	// Typically occupies 44 bits in GUID string.
	var guidCounterHex = guidCounter.toString(16)	// Initially occupies 4 bits in GUID string.
	guidCounter++
	var randomHex = Math.random().toString(16).substr(2)   // Typically occupies 32 bits in GUID string.
	var randomHex2= Math.random().toString(16).substr(2)   // Typically occupies 32 bits in GUID string.
	var randomHex3= Math.random().toString(16).substr(2)   // Typically occupies 32 bits in GUID string.
	// Append 30 zeros occupying 120 bits just in case (time-based and random values should not be empty and usually they will
	// exceed 128 bits, but for the sake of clarity when adding up to 128 GUID bits with M and N fields).
	var s = dateHex + guidCounterHex + randomHex + randomHex2 + randomHex3 + "000000000000000000000000000000"
	var N = (Math.floor(Math.random() * 4) + 8).toString(16)	// N field - occupies 4 bits (two fixed variant bits allow this to vary from [8, b]).
	var M = "4"	// Version field - occupies 4 bits.
	return [s.substr(0, 8), s.substr(8, 4), M + s.substr(12, 3), N + s.substr(15, 3), s.substr(18, 12)].join('-').toUpperCase()
}

/**
  Make short id. This function is provided, because most `Id` attribute values of WiX XML elements can have no more than 72 characters.
  */
function makeUniqueShortId(longId) {
	var hash = Utilities.getHash(longId)
	if (idHashTable[hash] === undefined)
		idHashTable[hash] = [longId]
	else
		idHashTable[hash].push(longId)

	return hash + idHashTable[hash].indexOf(longId)
}

/**
  This function looks for the specified dependent product in WiX product dependencies.
  */
function findDependentProductByName(productName) {
	if (productName === qtRuntimeProductMock["name"])
		return qtRuntimeProductMock

	for (var i in product.dependencies)
		if (product.dependencies[i].name === productName)
			return product.dependencies[i]
}

function cleanId(id) {
	// WiX allows only A-Z, a-z, digits, underscores (_) and periods (.) in the id.
	return Utilities.rfc1034Identifier(id).replace(/-/g, '.');
}

function getDirectoryId(path) {
	return "dir_" + makeUniqueShortId(path)
}

function getComponentGroupId(productName) {
	return "componentGroup_" + makeUniqueShortId(productName)
}

/**
  Get file component id.
  @param sourcePath file source path.
*/
function getFileComponentId(sourcePath) {
	return "component_" + makeUniqueShortId(sourcePath)
}

/**
  Get start menu shortcut id.
  @param sourcePath file source path.
*/
function getStartMenuShortcutId(sourcePath) {
	return "startMenuShortcut_" + makeUniqueShortId(sourcePath)
}

/**
  Get desktop shortcut id.
  @param sourcePath file source path.
*/
function getDesktopShortcutId(sourcePath) {
	return "desktopShortcut_" + makeUniqueShortId(sourcePath)
}

function getFeatureId(productName) {
	// Feature id may have maximally only 38 characters, therefore we have to use hash...
	return "feature_" + makeUniqueShortId(productName)
}

/**
  Get file id.
  @param sourcePath file source path.
*/
function getFileId(sourcePath) {
	return "file_" + makeUniqueShortId(sourcePath)
}

function getMergeId(msmPath) {
	return "merge_" + makeUniqueShortId(msmPath)
}

function dumpInstalldir(tree, parentElement, xmlFile)
{
	var subdirectories = tree["subdirectories"]
	for (var subdirectory in subdirectories) {
		var element = xmlFile.createElement("Directory")
		element.setAttribute("Id", getDirectoryId(subdirectories[subdirectory].path))
		element.setAttribute("Name", subdirectory)
		parentElement.appendChild(element)
		dumpInstalldir(subdirectories[subdirectory], element, xmlFile)
	}
}

function dumpFileComponentGroups(fileComponentGroups, parentElement, xmlFile)
{
	// Product name is the key of each component group value.
	for (var componentGroupProductName in fileComponentGroups) {
		var componentGroupElement = xmlFile.createElement("ComponentGroup")
		componentGroupElement.setAttribute("Id", getComponentGroupId(componentGroupProductName))
		parentElement.appendChild(componentGroupElement)
		var components = fileComponentGroups[componentGroupProductName]["components"]
		for (var componentKey in components) {
			var component = components[componentKey]
			var componentElement = xmlFile.createElement("Component")
			componentElement.setAttribute("Id", getFileComponentId(component["sourcePath"]))
			componentElement.setAttribute("Directory", getDirectoryId(component["installDir"]))
			componentElement.setAttribute("Guid", createGuid())

			var fileElement = xmlFile.createElement("File")
			// File id is constructed in a similar way to component id.
			fileElement.setAttribute("Id", getFileId(component["sourcePath"]))
			fileElement.setAttribute("KeyPath", "yes")
			fileElement.setAttribute("Source", FileInfo.toWindowsSeparators(component["installDir"] + "/" + FileInfo.fileName(component["sourcePath"])))
			componentElement.appendChild(fileElement)

			if (component["fileTags"].contains("application")) {
				var startMenuShortcutElement = xmlFile.createElement("Shortcut")
				var id = getStartMenuShortcutId(component["sourcePath"])
				startMenuShortcutElement.setAttribute("Id", id)
				startMenuShortcutElement.setAttribute("Directory", "startMenuDirectory")
				startMenuShortcutElement.setAttribute("Name", "!(loc." + id + "_Name)")
				startMenuShortcutElement.setAttribute("WorkingDirectory", getDirectoryId(component["installDir"]))
				if (product.iconAssignments[id] !== undefined) {
					startMenuShortcutElement.setAttribute("Icon", product.iconAssignments[id]["Id"])
					if (product.iconAssignments[id]["IconIndex"] !== undefined)
						startMenuShortcutElement.setAttribute("IconIndex", product.iconAssignments[id]["IconIndex"])
				}
				startMenuShortcutElement.setAttribute("Advertise", "yes")
				fileElement.appendChild(startMenuShortcutElement)

				var desktopShortcutElement = xmlFile.createElement("Shortcut")
				id = getDesktopShortcutId(component["sourcePath"])
				desktopShortcutElement.setAttribute("Id", id)
				desktopShortcutElement.setAttribute("Directory", "DesktopFolder")
				desktopShortcutElement.setAttribute("Name", "!(loc." + id + "_Name)")
				desktopShortcutElement.setAttribute("WorkingDirectory", getDirectoryId(component["installDir"]))
				if (product.iconAssignments[id] !== undefined) {
					desktopShortcutElement.setAttribute("Icon", product.iconAssignments[id]["Id"])
					if (product.iconAssignments[id]["IconIndex"] !== undefined)
						desktopShortcutElement.setAttribute("IconIndex", product.iconAssignments[id]["IconIndex"])
				}
				desktopShortcutElement.setAttribute("Advertise", "yes")
				fileElement.appendChild(desktopShortcutElement)
			}

			componentGroupElement.appendChild(componentElement)
		}
	}
}

function dumpMergeRefs(productName, parentFeatureElement, xmlFile)
{
	if (product.mergeModules[productName] !== undefined) {
		for (var i in product.mergeModules[productName]) {
			var msm = product.mergeModules[productName][i]
			var mergeRefElement = xmlFile.createElement("MergeRef")
			mergeRefElement.setAttribute("Id", getMergeId(msm))
			parentFeatureElement.appendChild(mergeRefElement)
		}
	}
}

function dumpFeatures(product, fileComponentGroups, parentElement, xmlFile)
{
	var rootFeatureElement = xmlFile.createElement("Feature")
	rootFeatureElement.setAttribute("Id", getFeatureId(product.name))
	rootFeatureElement.setAttribute("Title", "!(loc." + getFeatureId(product.name) + "_Title)")
	rootFeatureElement.setAttribute("Description", "!(loc." + getFeatureId(product.name) + "_Description)")
	rootFeatureElement.setAttribute("Level", "1")
	rootFeatureElement.setAttribute("ConfigurableDirectory", "INSTALLDIR")
	rootFeatureElement.setAttribute("AllowAdvertise", "no")
	rootFeatureElement.setAttribute("Absent", "disallow")
	parentElement.appendChild(rootFeatureElement)

	var groupRefElement = xmlFile.createElement("ComponentGroupRef")
	groupRefElement.setAttribute("Id", "startMenuComponentGroup")
	rootFeatureElement.appendChild(groupRefElement)

	dumpMergeRefs(product.name, rootFeatureElement, xmlFile)

	for (var componentGroupProductName in fileComponentGroups) {
		// If no products are featured all component groups will be listed in the scope of "root" feature.
		if (product.featuredProducts.length === 0) {
			groupRefElement = xmlFile.createElement("ComponentGroupRef")
			groupRefElement.setAttribute("Id", getComponentGroupId(componentGroupProductName))
			rootFeatureElement.appendChild(groupRefElement)
		} else {
			// List component groups as children of featured products.
			if (product.featuredProducts.contains(componentGroupProductName)) {
				var featuredProduct = findDependentProductByName(componentGroupProductName)
				var featureElement = xmlFile.createElement("Feature")
				featureElement.setAttribute("Id", getFeatureId(componentGroupProductName))
				featureElement.setAttribute("Title", "!(loc." + getFeatureId(componentGroupProductName) + "_Title)")
				featureElement.setAttribute("Description", "!(loc." + getFeatureId(componentGroupProductName) + "_Description)")
				featureElement.setAttribute("Level", "1")
				featureElement.setAttribute("AllowAdvertise", "no")
				featureElement.setAttribute("Absent", "disallow")
				rootFeatureElement.appendChild(featureElement)

				groupRefElement = xmlFile.createElement("ComponentGroupRef")
				groupRefElement.setAttribute("Id", getComponentGroupId(featuredProduct.name))
				featureElement.appendChild(groupRefElement)

				dumpMergeRefs(featuredProduct.name, featureElement, xmlFile)

				for (i in featuredProduct.dependencies) {
					var dependency = featuredProduct.dependencies[i]
					if (fileComponentGroups[dependency.name] !== undefined) {
						groupRefElement = xmlFile.createElement("ComponentGroupRef")
						groupRefElement.setAttribute("Id", getComponentGroupId(dependency.name))
						featureElement.appendChild(groupRefElement)
					}
				}
			}
		}
	}
}

function dumpMergeModules(product, parentElement, xmlFile)
{
	if (Object.keys(product.mergeModules).length === 0)
		return

	var directoryRefElement = xmlFile.createElement("DirectoryRef")
	directoryRefElement.setAttribute("Id", "TARGETDIR")
	parentElement.appendChild(directoryRefElement)

	for (var productName in product.mergeModules) {
		var msmList = product.mergeModules[productName]
		for (var i in msmList) {
			var msmPath = msmList[i]
			var mergeElement = xmlFile.createElement("Merge")
			mergeElement.setAttribute("Id", getMergeId(msmPath))
			mergeElement.setAttribute("SourceFile", msmPath)
			mergeElement.setAttribute("DiskId", "1")
			mergeElement.setAttribute("Language", "0")
			directoryRefElement.appendChild(mergeElement)
		}
	}
}

function dumpProductToWxs(product, inputs, upgradeCodeGuid, xmlFile)
{
	xmlFile.setContent("<?xml version=\"1.0\" encoding=\"" + product.xmlCodepage.toLowerCase() + "\"?>")

	var rootElement = xmlFile.createElement("Wix")
	rootElement.setAttribute("xmlns", "http://schemas.microsoft.com/wix/2006/wi")
	xmlFile.appendChild(rootElement)

	var productElement = xmlFile.createElement("Product")
	productElement.setAttribute("Name", "!(loc.ProductName)")
	productElement.setAttribute("Id", createGuid())
	productElement.setAttribute("UpgradeCode", upgradeCodeGuid)
	productElement.setAttribute("Language", product.productLanguage)
	productElement.setAttribute("Codepage", product.productCodepage)
	productElement.setAttribute("Version", product.productVersion)
	productElement.setAttribute("Manufacturer", product.productManufacturer)
	rootElement.appendChild(productElement)

	var packageElement = xmlFile.createElement("Package")
	packageElement.setAttribute("Id", "*")
	if (product.packageKeywords !== undefined)
		packageElement.setAttribute("Keywords", product.packageKeywords)
	packageElement.setAttribute("Description", "!(loc.PackageDescription)")
	packageElement.setAttribute("Manufacturer", product.packageManufacturer)
	packageElement.setAttribute("InstallerVersion", product.packageInstallerVersion)
	packageElement.setAttribute("Languages", product.packageLanguages)
	packageElement.setAttribute("Compressed", "yes")
	packageElement.setAttribute("SummaryCodepage", product.packageSummaryCodepage)
	productElement.appendChild(packageElement)

	var mediaElement = xmlFile.createElement("Media")
	mediaElement.setAttribute("Id", "1")
	mediaElement.setAttribute("Cabinet", product.name + ".cab")
	mediaElement.setAttribute("EmbedCab", "yes")
	productElement.appendChild(mediaElement)

	// Directories.
	var targetdirDirectoryElement = xmlFile.createElement("Directory")
	targetdirDirectoryElement.setAttribute("Id", "TARGETDIR")
	targetdirDirectoryElement.setAttribute("Name", "SourceDir")
	productElement.appendChild(targetdirDirectoryElement)

	var programMenuFolderDirectoryElement = xmlFile.createElement("Directory")
	programMenuFolderDirectoryElement.setAttribute("Id", "ProgramMenuFolder")
	targetdirDirectoryElement.appendChild(programMenuFolderDirectoryElement)

	var startMenuDirectoryElement = xmlFile.createElement("Directory")
	startMenuDirectoryElement.setAttribute("Id", product.startMenuDirectoryId)
	startMenuDirectoryElement.setAttribute("Name", product.startMenuDirectory)
	programMenuFolderDirectoryElement.appendChild(startMenuDirectoryElement)

	var desktopDirectoryElement = xmlFile.createElement("Directory")
	desktopDirectoryElement.setAttribute("Id", "DesktopFolder")
	desktopDirectoryElement.setAttribute("Name", "Desktop")
	targetdirDirectoryElement.appendChild(desktopDirectoryElement)

	var programFilesFolderDirectoryElement = xmlFile.createElement("Directory")
	programFilesFolderDirectoryElement.setAttribute("Id", product.programFilesFolderId)
	targetdirDirectoryElement.appendChild(programFilesFolderDirectoryElement)

	var installdirDirectoryElement = xmlFile.createElement("Directory")
	installdirDirectoryElement.setAttribute("Id", "INSTALLDIR")
	installdirDirectoryElement.setAttribute("Name", product.installdirDirectory)

	if (product.manufacturerInstallationDirectory !== undefined) {
		var manufacturerInstallationDirectoryElement = xmlFile.createElement("Directory")
		manufacturerInstallationDirectoryElement.setAttribute("Id", product.manufacturerInstallationDirectoryId)
		manufacturerInstallationDirectoryElement.setAttribute("Name", product.manufacturerInstallationDirectory)
		programFilesFolderDirectoryElement.appendChild(manufacturerInstallationDirectoryElement)
		manufacturerInstallationDirectoryElement.appendChild(installdirDirectoryElement)
	} else
		programFilesFolderDirectoryElement.appendChild(installdirDirectoryElement)

	var directoryTree = buildDirectoryTree(product, inputs)
	dumpInstalldir(directoryTree, installdirDirectoryElement, xmlFile)

	// Component groups.
	var startMenuComponentGroup = xmlFile.createElement("ComponentGroup")
	startMenuComponentGroup.setAttribute("Id", "startMenuComponentGroup")
	startMenuComponentGroup.setAttribute("Directory", product.startMenuDirectoryId)
	productElement.appendChild(startMenuComponentGroup)

	var startMenuComponent = xmlFile.createElement("Component")
	startMenuComponent.setAttribute("Id", "componentStartMenu")
	startMenuComponent.setAttribute("Guid", createGuid())
	startMenuComponentGroup.appendChild(startMenuComponent)

	var removeStartMenuFolderElement = xmlFile.createElement("RemoveFolder")
	removeStartMenuFolderElement.setAttribute("Id", "removeStartMenuFolder")
	removeStartMenuFolderElement.setAttribute("Directory", product.startMenuDirectoryId)
	removeStartMenuFolderElement.setAttribute("On", "uninstall")
	startMenuComponent.appendChild(removeStartMenuFolderElement)

	var startMenuRegistryValueElement = xmlFile.createElement("RegistryValue")
	startMenuRegistryValueElement.setAttribute("Root", "HKCU")
	startMenuRegistryValueElement.setAttribute("Key", "Software\\[Manufacturer]\\[ProductName]")
	startMenuRegistryValueElement.setAttribute("Type", "string")
	startMenuRegistryValueElement.setAttribute("Value", "")
	startMenuRegistryValueElement.setAttribute("KeyPath", "yes")
	startMenuComponent.appendChild(startMenuRegistryValueElement)

	var fileComponentGroups = buildFileComponentGroups(product, inputs)
	dumpFileComponentGroups(fileComponentGroups, productElement, xmlFile)

	// Features.
	dumpFeatures(product, fileComponentGroups, productElement, xmlFile)

	// Merge modules.
	dumpMergeModules(product, productElement, xmlFile)

	// UI Refs.
	for (i in product.uiRefIds) {
		var uiRefElement = xmlFile.createElement("UIRef")
		uiRefElement.setAttribute("Id", product.uiRefIds[i])
		productElement.appendChild(uiRefElement)
	}

	// Feature Refs.
	for (i in product.featureRefIds) {
		var featureRefElement = xmlFile.createElement("FeatureRef")
		featureRefElement.setAttribute("Id", product.featureRefIds[i])
		productElement.appendChild(featureRefElement)
	}

	// Icons.
	for (var iconId in product.icons) {
		var iconElement = xmlFile.createElement("Icon")
		iconElement.setAttribute("Id", iconId)
		iconElement.setAttribute("SourceFile", product.icons[iconId])
		productElement.appendChild(iconElement)
	}
	if (product.iconAssignments["ARPPRODUCTICON"] !== undefined) {
		var propertyElement = xmlFile.createElement("Property")
		propertyElement.setAttribute("Id", "ARPPRODUCTICON")
		propertyElement.setAttribute("Value", product.iconAssignments["ARPPRODUCTICON"]["Id"])
		productElement.appendChild(propertyElement)
	}

	// Other.
	if (product.majorUpgrade) {
		var majorUpgradeElement = xmlFile.createElement("MajorUpgrade")
		majorUpgradeElement.setAttribute("DowngradeErrorMessage", "!(loc.DowngradeErrorMessage)")
		productElement.appendChild(majorUpgradeElement)
	}
}

function getDefaultStringTranslation(id, fallbackValue) {
	if (product.defaultTranslations[product.defaultCulture] !== undefined
			&& product.defaultTranslations[product.defaultCulture][id] !== undefined)
		return product.defaultTranslations[product.defaultCulture][id]
	return fallbackValue
}

function dumpProductToWxl(product, inputs, xmlFile)
{
	xmlFile.setContent("<?xml version=\"1.0\" encoding=\"utf-8\"?>")

	var rootElement = xmlFile.createElement("WixLocalization")
	rootElement.setAttribute("xmlns", "http://schemas.microsoft.com/wix/2006/localization")
	rootElement.setAttribute("Culture", product.defaultCulture)
	xmlFile.appendChild(rootElement)

	if (product.majorUpgrade) {
		var stringElement = xmlFile.createElement("String")
		stringElement.setAttribute("Id", "DowngradeErrorMessage")
		stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation("DowngradeErrorMessage", "A later version of [ProductName] is already installed. Setup will now exit.")))
		rootElement.appendChild(stringElement)
	}

	stringElement = xmlFile.createElement("String")
	stringElement.setAttribute("Id", "ProductName")
	stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation("ProductName", product.friendlyName)))
	rootElement.appendChild(stringElement)

	stringElement = xmlFile.createElement("String")
	stringElement.setAttribute("Id", "PackageDescription")
	stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation("PackageDescription", product.description)))
	rootElement.appendChild(stringElement)

	stringElement = xmlFile.createElement("String")
	stringElement.setAttribute("Id", "PackageDescription")

	stringElement = xmlFile.createElement("String")
	var id = getFeatureId(product.name) + "_Title"
	stringElement.setAttribute("Id", id)
	stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation(id, product.friendlyName)))
	rootElement.appendChild(stringElement)

	stringElement = xmlFile.createElement("String")
	id = getFeatureId(product.name) + "_Description"
	stringElement.setAttribute("Id", id)
	stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation(id, product.description)))
	rootElement.appendChild(stringElement)

	var fileComponentGroups = buildFileComponentGroups(product, inputs)
	if (product.featuredProducts.length !== 0) {
		for (var componentGroupProductName in fileComponentGroups) {
			if (product.featuredProducts.contains(componentGroupProductName)) {
				var featuredProduct = findDependentProductByName(componentGroupProductName)
				stringElement = xmlFile.createElement("String")
				id = getFeatureId(componentGroupProductName) + "_Title"
				stringElement.setAttribute("Id", id)
				stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation(id, featuredProduct.friendlyName)))
				rootElement.appendChild(stringElement)

				stringElement = xmlFile.createElement("String")
				id = getFeatureId(componentGroupProductName) + "_Description"
				stringElement.setAttribute("Id", id)
				stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation(id, featuredProduct.description)))
				rootElement.appendChild(stringElement)
			}
		}
	}

	// Product name is the key of each component group value.
	for (componentGroupProductName in fileComponentGroups) {
		var components = fileComponentGroups[componentGroupProductName]["components"]
		for (var componentKey in components) {
			var component = components[componentKey]
			if (component["fileTags"].contains("application")) {
				stringElement = xmlFile.createElement("String")
				id = getStartMenuShortcutId(component["sourcePath"]) + "_Name"
				stringElement.setAttribute("Id", id)
				stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation(id, findDependentProductByName(componentGroupProductName).friendlyName)))
				rootElement.appendChild(stringElement)

				stringElement = xmlFile.createElement("String")
				id = getDesktopShortcutId(component["sourcePath"]) + "_Name"
				stringElement.setAttribute("Id", id)
				stringElement.appendChild(xmlFile.createTextNode(getDefaultStringTranslation(id, findDependentProductByName(componentGroupProductName).friendlyName)))
				rootElement.appendChild(stringElement)
			}
		}
	}
}

function getInstallDirFromInput(input)
{
	if  (input.qbs.installDir === undefined)
		return undefined

	var installDir = input.qbs.installSourceBase === undefined ? input.qbs.installDir
															   : input.qbs.installDir + "/" + FileInfo.path(FileInfo.relativePath(input.qbs.installSourceBase, input.filePath))
	return FileInfo.cleanPath(installDir)
}

function addDirectoryTreeEntry(directoryTree, sourcePath, installDir, productName)
{
	var dirs = installDir.split("/")
	var currentNode = directoryTree
	for (var dirIndex = 0; dirIndex < dirs.length; dirIndex++) {
		var dirName = dirs[dirIndex]
		if (currentNode["subdirectories"][dirName] === undefined) {
			currentNode["subdirectories"][dirName] = {
				"path": dirs.slice(0, dirIndex + 1).join("/"),
				"subdirectories": {},
				"files": [],
			}
		}
		currentNode = currentNode["subdirectories"][dirName]
	}
	currentNode["files"].push({
		// Always store full path as file name alone may not be unique accross products. This property should correspond with
		// "sorucePath" returned by buildFileCompoenentGroup().
		"sourcePath": FileInfo.fromWindowsSeparators(sourcePath),
		"productName": productName,
	})
}

/**
  Get directory tree containing all target installation directories used by the product and its dependencies. Some other information
  is also stored in the tree.
  */
function buildDirectoryTree(product, inputs)
{
	var directoryTree = {
		"subdirectories": {},
		"files": [],
	}

	for (var tagIndex = 0; tagIndex < product.inputFileTags.length; tagIndex++) {
		var tagInputs = inputs[product.inputFileTags[tagIndex]]
		if (tagInputs === undefined)
			continue

		if (product.inputFileTags[tagIndex] === "cutehmi.windeployqt.json") {
			for (var i = 0; i < tagInputs.length; i++) {
				console.log("Found " + tagInputs[i].filePath + " which will be used as a source of directory data.")
				var jsonFile = new TextFile(tagInputs[i].filePath, TextFile.ReadOnly)
				try  {
					var json = JSON.parse(jsonFile.readAll())
				} finally {
					jsonFile.close()
				}
				for (var entryIndex in json["files"]) {
					var entry = json["files"][entryIndex]
					var installDir = FileInfo.relativePath(product.qbs.installRoot + product.qbs.installPrefix, entry["target"])
					addDirectoryTreeEntry(directoryTree, entry["source"], installDir, qtRuntimeProductMock["name"])
				}
			}
		} else if (product.inputFileTags[tagIndex] === "installable") {
			for (i = 0; i < tagInputs.length; i++) {
				installDir = getInstallDirFromInput(tagInputs[i])
				// This normally shouldn't happen for installable files.
				if (installDir === undefined) {
					console.warn("File " + tagInputs[i].filePath + " is not installable and it won't be listed in " + output.filePath)
					continue
				}
				addDirectoryTreeEntry(directoryTree, tagInputs[i].filePath, installDir, tagInputs[i].product.name)
			}
		} else
			console.warn("Unsupported file tag '" + product.inputFileTags[tagIndex] + "' used in inputs")
	}

	return directoryTree
}

function addFileComponentGroupEntry(fileComponentGroups, sourcePaths, sourcePath, installDir, fileTags, productName)
{
	// Prevent adding duplicates.
	if (sourcePaths.contains(sourcePath))
		return
	sourcePaths.push(sourcePath)

	// By principle product name is the key of each component group.
	if (fileComponentGroups[productName] === undefined) {
		fileComponentGroups[productName] = {
			"components": [],
		}
	}

	fileComponentGroups[productName]["components"].push({
		// Always store full path as file name alone may not be unique accross products. This property should correspond with
		// "sourcePath" returned by buildDirectoryTree().
		"sourcePath": FileInfo.fromWindowsSeparators(sourcePath),
		"installDir": installDir,
		"fileTags": fileTags,
	})
}

/**
  Build component groups.

  Imporatant property of resulted object is that product name is used as the key for each component groups (note that this does not
  need to hold true for the `Id` property in the `wxs` file - use getComponentGroupId() function to obtain the `Id` for a specific
  group).
  */
function buildFileComponentGroups(product, inputs)
{
	var fileComponentGroups = {}
	var sourcePaths = []	// Used to prevent duplicates (JSON files produced by windeployqt contain duplicates).

	for (var tagIndex = 0; tagIndex < product.inputFileTags.length; tagIndex++) {
		var tagInputs = inputs[product.inputFileTags[tagIndex]]
		if (tagInputs === undefined)
			continue

		if (product.inputFileTags[tagIndex] === "cutehmi.windeployqt.json") {
			for (var i = 0; i < tagInputs.length; i++) {
				console.log("Found " + tagInputs[i].filePath + " which will be used as a source of component groups data.")
				var jsonFile = new TextFile(tagInputs[i].filePath, TextFile.ReadOnly)
				try  {
					var json = JSON.parse(jsonFile.readAll())
				} finally {
					jsonFile.close()
				}
				for (var entryIndex in json["files"]) {
					var entry = json["files"][entryIndex]

					//<WixInstaller-1.workaround target="windeployqt" cause="bug">
					// Check if file exists in target location and copy it if _windeployqt_ failed to do so.
					var fileName = FileInfo.fileName(FileInfo.fromWindowsSeparators(entry["source"]))
					var targetPath = entry["target"] + "\\" + fileName
					if (!File.exists(targetPath))
						File.copy(entry["source"], targetPath)
					//</WixInstaller-1.workaround>

					var installDir = FileInfo.relativePath(product.qbs.installRoot + product.qbs.installPrefix, entry["target"])
					addFileComponentGroupEntry(fileComponentGroups, sourcePaths, entry["source"], installDir, [], qtRuntimeProductMock["name"])
				}
			}
		} else if (product.inputFileTags[tagIndex] === "installable") {
			for (i = 0; i < tagInputs.length; i++) {
				installDir = getInstallDirFromInput(tagInputs[i])
				if (installDir === undefined) {
					console.warn("File " + tagInputs[i].filePath + " is not installable and it won't be listed in " + output.filePath)
					continue
				}
				addFileComponentGroupEntry(fileComponentGroups, sourcePaths, tagInputs[i].filePath, installDir, tagInputs[i].fileTags, tagInputs[i].product.name)
			}
		} else
			console.warn("Unsupported file tag '" + product.inputFileTags[tagIndex] + "' used in inputs")
	}

	return fileComponentGroups
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
