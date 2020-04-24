#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_EVENTWRITER_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_EVENTWRITER_HPP

#include "internal/common.hpp"
#include "internal/EventCollective.hpp"
#include "AbstractWriter.hpp"

#include <cutehmi/services/Serviceable.hpp>

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API EventWriter:
	public AbstractWriter
{
		Q_OBJECT

	public:
		EventWriter(QObject * parent = nullptr);

		virtual std::unique_ptr<ServiceStatuses> configureStarting(QState * starting) override;

		virtual std::unique_ptr<ServiceStatuses> configureStarted(QState * active, const QState * idling, const QState * yielding) override;

		virtual std::unique_ptr<ServiceStatuses> configureStopping(QState * stopping) override;

		virtual std::unique_ptr<ServiceStatuses> configureBroken(QState * broken) override;

		virtual std::unique_ptr<ServiceStatuses> configureRepairing(QState * repairing) override;

		virtual std::unique_ptr<ServiceStatuses> configureEvacuating(QState * evacuating) override;

		virtual std::unique_ptr<QAbstractTransition> transitionToStarted() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToStopped() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToBroken() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToYielding() const override;

		virtual std::unique_ptr<QAbstractTransition> transitionToIdling() const override;

	private slots:
		void onSchemaChanged();

		void insertEvent(TagValue * tag);

		void connectTagSignals();

		void disconnectTagSignals();

	private:
		std::unique_ptr<services::Serviceable::ServiceStatuses> configureStartingOrRepairing(QState * parent);

		struct Members
		{
			internal::EventCollective dbCollective;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
