/**
  Project cloner.

  To make the project clonable it must use one of the cutehmi.ProjectGroup items (cutehmi.ToolProject or cutehmi.ExtensionProject),
  which provide extra `groupName` property.

  Files which are going to be copied must be referenced in one of the products belonging to the project group.

  Files tagged with 'cutehmi.clone.exclude' won't be cloned.

  To clone the project set Qbs `modules.cutehmi.clone.projects` property according to the pattern:
  `modules.cutehmi.clone.projects:<old project>,<new project>`. For example to clone Templates.CppPluginSkeleton.0 into
  My.Extension.0 set following:

  ```
  modules.cutehmi.clone.projects:Templates.CppPluginSkeleton.0,My.Extension.0
  ```

  Note that most of the product-specific elements such as export macros, namespaces, etc are currently not refactored automatically.
  */
Module {
	readonly property bool enabled: oldProject !== undefined && newProject !== undefined

	property stringList projects: undefined

	property string oldProject: projects !== undefined ? projects[0] : undefined

	property string newProject: projects !== undefined ? projects[1] : undefined
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
