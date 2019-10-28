#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_POLLINGTIMER_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_POLLINGTIMER_HPP

#include "internal/common.hpp"

#include <QObject>

namespace cutehmi {
namespace services {

/**
 * Polling timer. Polling timer is a simple, single-shot timer, useful when dealing with polling. It allows for dynamic
 * creation of subtimers, which may be used to control execution of individual tasks into which polling process can be decomposed.
 */
class CUTEHMI_SERVICES_API PollingTimer:
	public QObject
{
		Q_OBJECT

	public:
		static constexpr int INITIAL_INTERVAL = 250;
		static constexpr int INITIAL_SUBTIMER_INTERVAL = 10;

		Q_PROPERTY(int interval READ interval WRITE setlInterval NOTIFY intervalChanged)
		Q_PROPERTY(PollingTimer * subtimer READ subtimer CONSTANT)

		explicit PollingTimer(int interval = INITIAL_INTERVAL, QObject * parent = nullptr);

		int interval() const;

		void setlInterval(int interval);

		/**
		 * Get subtimer. Subtimers are created dynamically, whenever some piece of code wants to access it.
		 * @return subtimer.
		 */
		PollingTimer * subtimer();

	public slots:
		/**
		 * Start timer.
		 */
		void start();

	signals:
		void intervalChanged();

		void triggered();

	private slots:
		void shoot();

	private:
		struct Members {
			int interval;
			PollingTimer * subtimer;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
