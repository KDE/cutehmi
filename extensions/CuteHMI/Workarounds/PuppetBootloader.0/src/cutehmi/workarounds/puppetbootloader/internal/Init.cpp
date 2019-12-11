#include "Init.hpp"

#include <QMutex>

namespace cutehmi {
namespace workarounds {
namespace puppetbootloader {
namespace internal {

Init::Init():
	m_initialized(false)
{
	QMutexLocker lock(& m_mutex);

	if (!m_initialized)
		_Construct();

	m_initialized = true;
}

Init::~Init()
{
	QMutexLocker lock(& m_mutex);

	if (m_initialized)
		_Destroy();

	m_initialized = false;
}

}
}
}
}
