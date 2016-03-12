#ifndef CUTEHMI_LIBBASE_SRC_BASE_IRUNNER_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_IRUNNER_HPP

#include "../platform.hpp"

namespace cutehmi {
namespace base {

class IRunner
{
	public:
		virtual void start() = 0;

		virtual void stop() = 0;

	protected:
		virtual ~IRunner() = default;

		IRunner() = default;
};

}
}

#endif

