#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_POLLINGITERATOR_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_POLLINGITERATOR_HPP

#include "common.hpp"
#include "IterableTasks.hpp"

#include <QUuid>

namespace cutehmi {
namespace modbus {

class AbstractDevice;

namespace internal {

class CUTEHMI_MODBUS_PRIVATE PollingIterator:
	public IterableTasks
{
	public:
		PollingIterator(AbstractDevice * device);

		bool runNext() override;

		void reset() override;

		QUuid & requestId();

		const QUuid & requestId() const;

	private:
		typedef std::vector<std::unique_ptr<internal::IterableTasks>> TasksCointainer;

		TasksCointainer::iterator m_currentTask;
		TasksCointainer m_tasks;
		QUuid m_requestId;
};

}
}
}

#endif
