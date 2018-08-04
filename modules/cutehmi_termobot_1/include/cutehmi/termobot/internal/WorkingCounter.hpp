#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_INTERNAL_WORKINGCOUNTER_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_INTERNAL_WORKINGCOUNTER_HPP

#include <functional>

namespace cutehmi {
namespace termobot {
namespace internal {

class WorkingCounter
{
	public:
		WorkingCounter(std::function<void()> busyChanged);

		WorkingCounter & operator ++();

		WorkingCounter & operator --();

		operator bool() const;

		int m_counter;
	private:
		std::function<void()> m_busyChanged;
};

}
}
}

#endif
