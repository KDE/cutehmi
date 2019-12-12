#ifndef H_EXTENSIONS_CUTEHMI_WORKAROUNDS_PUPPETBOOTLOADER_0_SRC_CUTEHMI_WORKAROUNDS_PUPPETBOOTLOADER_INTERNAL_INIT_HPP
#define H_EXTENSIONS_CUTEHMI_WORKAROUNDS_PUPPETBOOTLOADER_0_SRC_CUTEHMI_WORKAROUNDS_PUPPETBOOTLOADER_INTERNAL_INIT_HPP

#include <QMutex>

namespace cutehmi {
namespace workarounds {
namespace puppetbootloader {
namespace internal {

class Init final
{
	public:
		Init();

		~Init();

	private:
		static void _Construct();

		static void _Destroy();

		QMutex m_mutex;
		bool m_initialized;
};

}
}
}
}

#endif
