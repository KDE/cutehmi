import "functions.js" as Functions

/**
  Naming conventions. This module groups properties that provide values for a specific extension, to be used with various language
  and application constructs, generated according to the conventions from core CommonProduct properties (such as 'name').
 */
Module {
	PropertyOptions {
		name: "productName"
		description: "Product name. Defaults to name of the product that declares dependency."
	}
	property string productName: product.name

	PropertyOptions {
		name: "baseName"
		description: "Product base name. Defaults to base name of the product that declares dependency."
	}
	property string baseName: product.baseName !== undefined ? product.baseName : product.name

	PropertyOptions {
		name: "debugOutput"
		description: "Debug output. When enabled module will print generated values to standard output."
	}
	property bool debugOutput: false

	PropertyOptions {
		name: "namespace"
		description: "C++ namespace qualifier."
	}
	readonly property string namespace: baseName.toLowerCase().replace(/\./g, '::')

	PropertyOptions {
		name: "namespaceArray"
		description: "C++ namespace array. Contains parts of a namespace as array elements. Useful for pre-C++17 nested namespace definitions."
	}
	readonly property stringList namespaceArray: baseName.toLowerCase().split('.')

	PropertyOptions {
		name: "macroPrefix"
		description: "C++ macro prefix. Supposed to be used when defining API-related macros."
	}
	readonly property string macroPrefix: baseName.toUpperCase().replace(/\./g, '_')

	PropertyOptions {
		name: "longMacroPrefix"
		description: "C++ \"long\" macro prefix. Includes major version. Supposed to be used when dealing with unique macros."
	}
	readonly property string longMacroPrefix: productName.toUpperCase().replace(/\./g, '_')

	PropertyOptions {
		name: "loggingCategory"
		description: "Logging category function name."
	}
	readonly property string loggingCategory: baseName.toLowerCase().replace(/\./g, '_') + "_loggingCategory"

	PropertyOptions {
		name: "dedicatedSubdir"
		description: "Subdirectory dedicated to keep header and source files within product subdirectory."
	}
	readonly property string dedicatedSubdir: baseName.toLowerCase().replace(/\./g, '/')

	PropertyOptions {
		name: "includeDir"
		description: "Directory dedicated to keep product's public C++ header files."
	}
	readonly property string includeDir: product.sourceDirectory + "/include/" + dedicatedSubdir

	PropertyOptions {
		name: "sourceDir"
		description: "Directory dedicated to keep product's C++ source files."
	}
	readonly property string sourceDir: product.sourceDirectory + "/src/" + dedicatedSubdir

	PropertyOptions {
		name: "internalIncludeDir"
		description: "Directory dedicated to keep product's internal C++ header files."
	}
	readonly property string internalIncludeDir: includeDir + "/internal"

	PropertyOptions {
		name: "internalSourceDir"
		description: "Directory dedicated to keep product's C++ source files corresponding to internal header files."
	}
	readonly property string internalSourceDir: sourceDir + "/internal"

	PropertyOptions {
		name: "testsDir"
		description: "Directory dedicated to keep product test files."
	}
	readonly property string testsDir: product.sourceDirectory + "/tests"

	PropertyOptions {
		name: "qmlModuleIdentifier"
		description: "Respective identifier of a QML module represented by an extension."
	}
	readonly property string qmlModuleIdentifier: baseName

	PropertyOptions {
		name: "qmlPluginName"
		description: "Name of QML plugin binary (as expected by QML importer - not a filename with various suffixes)."
	}
	readonly property string qmlPluginName: product.name

	PropertyOptions {
		name: "qmlPluginSource"
		description: "Standard filename pattern of a source file that implements QQmlExtensionPlugin derived class."
	}
	readonly property string qmlPluginSource: "QMLPlugin.cpp"

	PropertyOptions {
		name: "qmlPluginClassName"
		description: "Standard, qualified name of a QQmlExtensionPlugin derived class."
	}
	readonly property string qmlPluginClassName: namespace + "::internal::QMLPlugin"

	PropertyOptions {
		name: "qmlTypeInfo"
		description: "Standard name of QML type description file."
	}
	readonly property string qmlTypeInfo: "plugins.qmltypes"

	PropertyOptions {
		name: "initClassName"
		description: "Standard name of Init class used to initialize extension."
	}
	readonly property string initClassName: namespace + "::Init"

	PropertyOptions {
		name: "initHeader"
		description: "Header file with Init class declaration."
	}
	readonly property string initHeader: dedicatedSubdir + "/Init.hpp"

	PropertyOptions {
		name: "hyphenatedName"
		description: "Lowercased product name written with hyphens instead of dots."
	}
	readonly property string hyphenatedName: productName.toLowerCase().replace(/\./g, '-')

	PropertyOptions {
		name: "functions"
		description: "This property exposes various helper functions."
	}
	readonly property var functions: Functions

	validate: {
		if (debugOutput) {
			console.info(" ")
			console.info("Module '" + name + "' has generated following property values for product '" + productName + "'")
			console.info("namespace: '" + namespace + "'")
			console.info("namespaceArray: '" + JSON.stringify(namespaceArray) + "'")
			console.info("macroPrefix: '" + macroPrefix + "'")
			console.info("longMacroPrefix: '" + longMacroPrefix + "'")
			console.info("loggingCategory: '" + loggingCategory + "'")
			console.info("dedicatedSubdir: '" + dedicatedSubdir + "'")
			console.info("includeDir: '" + includeDir + "'")
			console.info("sourceDir: '" + sourceDir + "'")
			console.info("internalIncludeDir: '" + internalIncludeDir + "'")
			console.info("internalSourceDir: '" + internalSourceDir + "'")
			console.info("testsDir: '" + testsDir + "'")
			console.info("qmlModuleIdentifier: '" + qmlModuleIdentifier + "'")
			console.info("qmlPluginName : '" + qmlPluginName + "'")
			console.info("qmlPluginSource: '" + qmlPluginSource + "'")
			console.info("qmlPluginClassName: '" + qmlPluginClassName + "'")
			console.info("qmlTypeInfo: '" + qmlTypeInfo + "'")
			console.info("initClassName: '" + initClassName + "'")
			console.info("initHeader: '" + initHeader + "'")
			console.info("hyphenatedName: '" + hyphenatedName + "'")
			console.info("---")
		}
	}

}

//(c)C: Copyright © 2019-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
