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

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
