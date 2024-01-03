import "functions.js" as Functions

/**
  Naming conventions. This module is used to generates values from core CommonProduct properties (such as 'name') according to
  CuteHMI naming conventions.
 */
Module {
	PropertyOptions {
		name: "debugOutput"
		description: "Debug output. When enabled module will print generated values to standard output."
	}
	property bool debugOutput: false

	PropertyOptions {
		name: "functions"
		description: "This property exposes various functions."
	}
	readonly property var functions: Functions

	validate: {
		if (debugOutput) {
			console.info(" ")
			console.info("Module '" + name + "' has generated following property values for product '" + product.name + "'")
			console.info("namespace: '" + Functions.namespace(product.name) + "'")
			console.info("namespaceArray: '" + JSON.stringify(Functions.namespaceArray(product.name)) + "'")
			console.info("macroPrefix: '" + Functions.macroPrefix(product.name) + "'")
			console.info("longMacroPrefix: '" + Functions.longMacroPrefix(product.name) + "'")
			console.info("loggingCategory: '" + Functions.loggingCategory(product.name) + "'")
			console.info("dedicatedSubdir: '" + Functions.dedicatedSubdir(product.name) + "'")
			console.info("includesSubdir: '" + Functions.includesSubdir(product.name) + "'")
			console.info("sourcesSubdir: '" + Functions.sourcesSubdir(product.name) + "'")
			console.info("internalIncludesSubdir: '" + Functions.internalIncludesSubdir(product.name) + "'")
			console.info("internalSourcesSubdir: '" + Functions.internalSourcesSubdir(product.name) + "'")
			console.info("autogenIncludesSubdir: '" + Functions.autogenIncludesSubdir(product.name) + "'")
			console.info("autogenSourcesSubdir: '" + Functions.autogenSourcesSubdir(product.name) + "'")
			console.info("testsSubdir: '" + Functions.testsSubdir(product.name) + "'")
			console.info("qmlModuleIdentifier: '" + Functions.qmlModuleIdentifier(product.name) + "'")
			console.info("qmlPluginName : '" + Functions.qmlPluginName(product.name) + "'")
			console.info("qmlPluginSource: '" + Functions.qmlPluginSource(product.name) + "'")
			console.info("qmlPluginClassName: '" + Functions.qmlPluginClassName(product.name) + "'")
			console.info("qmlTypeInfo: '" + Functions.qmlTypeInfo(product.name) + "'")
			console.info("initClassName: '" + Functions.initClassName(product.name) + "'")
			console.info("initHeader: '" + Functions.initHeader(product.name) + "'")
			console.info("hyphenatedName: '" + Functions.hyphenatedName(product.name) + "'")
			console.info("---")
		}
	}

}

//(c)C: Copyright © 2019-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
