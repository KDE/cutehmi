#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCLIENTCONFIG_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DUMMYCLIENTCONFIG_HPP

#include "common.hpp"

#include <QObject>
#include <QReadWriteLock>

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE DummyClientConfig:
	public QObject
{
		Q_OBJECT

	public:
		static constexpr int INITIAL_OPEN_LATENCY = 1000;
		static constexpr int INITIAL_CLOSE_LATENCY = 1000;
		static constexpr int INITIAL_LATENCY = 1000;

		explicit DummyClientConfig(QObject * parent = nullptr);

		int openLatency() const;

		void setOpenLatency(int openLatency);

		int closeLatency() const;

		void setCloseLatency(int closeLatency);

		int latency() const;

		void setLatency(int latency);

	signals:
		void configChanged();

	private:
		struct Members
		{
			int	openLatency = INITIAL_OPEN_LATENCY;
			int closeLatency = INITIAL_CLOSE_LATENCY;
			int latency = INITIAL_LATENCY;
			mutable QReadWriteLock lock;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
