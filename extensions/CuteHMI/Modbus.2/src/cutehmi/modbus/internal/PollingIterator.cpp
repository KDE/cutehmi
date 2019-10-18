#include <cutehmi/modbus/internal/PollingIterator.hpp>

#include <cutehmi/modbus/AbstractDevice.hpp>
#include <cutehmi/modbus/internal/HoldingRegisterPolling.hpp>
#include <cutehmi/modbus/internal/CoilPolling.hpp>
#include <cutehmi/modbus/internal/DiscreteInputPolling.hpp>
#include <cutehmi/modbus/internal/InputRegisterPolling.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

PollingIterator::PollingIterator(AbstractDevice * device):
	m_requestId(nullptr)
{
	m_tasks.emplace_back(std::unique_ptr<internal::IterableTasks>(new internal::CoilPolling(device, & m_requestId)));
	m_tasks.emplace_back(std::unique_ptr<internal::IterableTasks>(new internal::DiscreteInputPolling(device, & m_requestId)));
	m_tasks.emplace_back(std::unique_ptr<internal::IterableTasks>(new internal::HoldingRegisterPolling(device, & m_requestId)));
	m_tasks.emplace_back(std::unique_ptr<internal::IterableTasks>(new internal::InputRegisterPolling(device, & m_requestId)));
	m_currentTask = m_tasks.begin();
}

bool PollingIterator::runNext()
{
	while (m_currentTask != m_tasks.end()) {
		if ((*m_currentTask)->runNext())
			return true;
		++m_currentTask;
	}
	return false;
}

void PollingIterator::reset()
{
	m_requestId = nullptr;
	m_currentTask = m_tasks.begin();
	for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it)
		(*it)->reset();
}

QUuid & PollingIterator::requestId()
{
	return m_requestId;
}

const QUuid & PollingIterator::requestId() const
{
	return m_requestId;
}

}
}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
