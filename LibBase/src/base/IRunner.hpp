#ifndef IRUNNER
#define IRUNNER

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

#endif // IRUNNER

