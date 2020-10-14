#include "Init.hpp"

#include <QMutexLocker>
#include <QFileInfo>
#include <QCoreApplication>
#include <QtDebug>

#include <Windows.h>

#include <cstring>
#include <memory>

namespace cutehmi {
namespace workarounds {
namespace puppetbootloader {
namespace internal {

static constexpr const char * TARGET_APP = "Qml2Puppet";

static HMODULE DllHandle;
static std::unique_ptr<char[]> OldPath;

void Init::_Construct()
{
	// Proceed only if we run from target application.
	if (QCoreApplication::applicationName() != TARGET_APP)
		return;

	// Obtain handle to PuppetBootloader library itself.
	if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
						   reinterpret_cast<LPCSTR>(& Init::_Construct), & DllHandle) == 0) {
		qCritical() << "Function GetModuleHandleExA() failed with error code " << GetLastError() << ".";
		return;
	}

	// Store old DLL path.
	DWORD oldPathLength = GetDllDirectoryA(0, OldPath.get());
	OldPath.reset(new char[oldPathLength]);
	GetDllDirectoryA(oldPathLength, OldPath.get());

	// GetModuleFileName() won't return required length, so for the sake of simplicity stick with MAX_PATH for now and perform critical exit if path is too long.
	std::unique_ptr<char[]> dllPath(new char[MAX_PATH]);
	DWORD dllPathLength = GetModuleFileNameA(DllHandle, dllPath.get(), MAX_PATH);
	if (dllPathLength == MAX_PATH) {
		qCritical() << "Runtime path '" << dllPath.get() << "' (truncated) exceeds maximal length of " << MAX_PATH << " characters supported by '" << Q_FUNC_INFO << "'.";
		return;
	}

	// PuppetBootloader resides in directory with other libraries, so its directory should now be added to DLL search paths.
	QFileInfo dllPathInfo(dllPath.get());
	QFileInfo oldPathInfo(OldPath.get());

	// Do not override DLL path if it has been already set by something as strange as PuppetBootloader... it would probably break that thing.
	if ((strlen(OldPath.get()) > 0) && (oldPathInfo.canonicalPath() != dllPathInfo.canonicalPath())) {
		qCritical() << "Can not override DLL search directory, which has been already set to '" << OldPath.get() << "'.";
		return;
	}

	// Main event of the evening - add directory with libraries to DLL search paths, so that TARGET_APP can load plugins with dependencies.
	SetDllDirectoryA(dllPathInfo.canonicalPath().toLocal8Bit().constData());

	// And people say SetDllDirectory() is useless, huh...
}

void Init::_Destroy()
{
	if (QCoreApplication::applicationName() != TARGET_APP)
			return;

	if (strlen(OldPath.get()) == 0)
			SetDllDirectoryA(nullptr);
	else
		SetDllDirectoryA(OldPath.get());
}

}
}
}
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
