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

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
