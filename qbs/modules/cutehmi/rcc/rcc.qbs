import qbs
import qbs.Utilities

/**
  This module generates 'rcc' artifact. By default input files must be marked with "cutehmi.qrc" tag. This prevents `Qt.core`
  module, which uses `qrc` file tag from creating `cpp` resource files, which later can cause problems due to rules invoking
  compiler/linker on simple QML extensions. This behavior can be changed however by setting `inputFileTags` property.
  */
Module {
	additionalProductTypes: ["cutehmi.rcc"]

	property string rccProgram: "rcc"

	property stringList inputFileTags: ["cutehmi.qrc"]

	Depends { name: "Qt.core" }

	Rule {
		inputs: product.cutehmi.rcc.inputFileTags
		outputFileTags: ["rcc", "cutehmi.rcc"]
		outputArtifacts: {
			return [{
						filePath: input.completeBaseName + ".rcc",
						fileTags: ["rcc", "cutehmi.rcc"]
			}]
		}

		prepare: {
			var rccProgram = product.cutehmi.rcc.rccProgram
			var args = [input.filePath, "-binary", "-o", output.filePath]
			 if (input.Qt.core.enableBigResources)
				 args.push("-pass", "1")
			 var rccPath = Utilities.versionCompare(product.Qt.core.version, "6.1") < 0 ? product.Qt.core.binPath + '/rcc'
																						: product.Qt.core.libExecPath + '/rcc'
			 var cmd = new Command(rccPath, args);
			 cmd.highlight = 'codegen'
			 cmd.description = "invoking '" + rccProgram + "' program to generate '" + output.filePath + "'"
			 return cmd
		}
	}
}

//(c)C: Copyright © 2021-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
