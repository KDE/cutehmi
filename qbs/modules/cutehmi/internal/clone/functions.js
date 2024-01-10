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

//(c)C: Copyright © 2024, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
