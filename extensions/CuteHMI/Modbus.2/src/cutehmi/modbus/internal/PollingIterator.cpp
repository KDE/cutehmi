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
