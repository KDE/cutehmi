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
	// Porceed only if we run from target application.
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
