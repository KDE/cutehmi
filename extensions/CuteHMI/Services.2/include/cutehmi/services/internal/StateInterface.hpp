#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_INTERNAL_STATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_INTERNAL_STATEINTERFACE_HPP

#include "common.hpp"

#include <QObject>
#include <QState>
#include <QSignalTransition>

#include <array>

namespace cutehmi {
namespace services {
namespace internal {

class CUTEHMI_SERVICES_API StateInterface:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

		StateInterface(QObject * parent = nullptr);

		QString status() const;

		void setStatus(const QString & status);

		Q_INVOKABLE QAbstractState * find(const QString & name);

		QState & stopped();

		const QState & stopped() const;

		QState & interrupted();

		const QState & interrupted() const;

		QState & starting();

		const QState & starting() const;

		QState & started();

		const QState & started() const;

		QState & idling();

		const QState & idling() const;

		QState & yielding();

		const QState & yielding() const;

		QState & active();

		const QState & active() const;

		QState & stopping();

		const QState & stopping() const;

		QState & broken();

		const QState & borken() const;

		QState & repairing();

		const QState & repairing() const;

		QState & evacuating();

		const QState & evacuating() const;

	signals:
		void statusChanged();

	private:
		struct Members
		{
			enum MainStateNames : std::size_t {
				STOPPED = 0,
				INTERRUPTED,
				STARTING,
				STARTED,
				STOPPING,
				BROKEN,
				REPAIRING,
				EVACUATING
			};

			typedef std::array<QState, 8> MainStatesContainer;

			MainStatesContainer mainStates;
			QString status;
			QState * idling;
			QState * yielding;
			QState * active;

			Members():
				mainStates{},
				idling(new QState(& mainStates[STARTED])),
				yielding(new QState(& mainStates[STARTED])),
				active(new QState(& mainStates[STARTED]))
			{
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
