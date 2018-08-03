#include "../../../../include/cutehmi/termobot/internal/WorkingCounter.hpp"

#include <QObject>

namespace cutehmi {
namespace termobot {
namespace internal {

WorkingCounter::WorkingCounter(std::function<void ()> busyChanged):
	m_counter(0),
	m_busyChanged(busyChanged)
{
}


WorkingCounter & WorkingCounter::operator ++()
{
	m_counter++;
	if (m_counter == 1)
		emit m_busyChanged();

	return *this;
}

WorkingCounter & WorkingCounter::operator --()
{
	m_counter--;
	if (m_counter == 0)
		emit m_busyChanged();

	return *this;
}

WorkingCounter::operator bool() const
{
	return static_cast<bool>(m_counter);
}

}
}
}
