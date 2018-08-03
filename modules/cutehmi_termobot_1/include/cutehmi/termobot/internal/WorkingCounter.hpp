#ifndef WORKINGCOUNTER_HPP
#define WORKINGCOUNTER_HPP

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

#endif // WORKINGCOUNTER_HPP
