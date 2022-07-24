#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_ABSTRACTLISTMODEL_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_ABSTRACTLISTMODEL_HPP

#include "internal/common.hpp"
#include "internal/DbServiceableMixin.hpp"
#include "Schema.hpp"

#include <cutehmi/services/Serviceable.hpp>

#include <QAbstractListModel>

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API AbstractListModel:
	public QAbstractListModel,
	public services::Serviceable,
	private internal::DbServiceableMixin<AbstractListModel>
{
		Q_OBJECT

		friend class internal::DbServiceableMixin<AbstractListModel>;

	public:
		static constexpr int INITIAL_INTERVAL = 1000;

		/**
		  busy status. Indicates that object is busy processing SQL request.
		  */
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

		/**
		  Interval [ms] between updates.

		  @assumption{cutehmi::dataacquisition::AbstractDataModel-interval_non_negative}
		  Value of @a interval property should be non-negative.
		  */
		Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

		Q_PROPERTY(cutehmi::dataacquisition::Schema * schema READ schema WRITE setSchema NOTIFY schemaChanged)

		AbstractListModel(QObject * parent = nullptr);

		virtual bool busy() const = 0;

		int interval() const;

		void setInterval(int interval);

		Schema * schema() const;

		void setSchema(Schema * schema);

		std::unique_ptr<ServiceStatuses> configureStarting(QState * starting) override;

		std::unique_ptr<ServiceStatuses> configureStarted(QState * active, const QState * idling, const QState * yielding) override;

		std::unique_ptr<ServiceStatuses> configureStopping(QState * stopping) override;

		std::unique_ptr<ServiceStatuses> configureBroken(QState * broken) override;

		std::unique_ptr<ServiceStatuses> configureRepairing(QState * repairing) override;

		std::unique_ptr<ServiceStatuses> configureEvacuating(QState * evacuating) override;

		std::unique_ptr<QAbstractTransition> transitionToStarted() const override;

		std::unique_ptr<QAbstractTransition> transitionToStopped() const override;

		std::unique_ptr<QAbstractTransition> transitionToBroken() const override;

		std::unique_ptr<QAbstractTransition> transitionToYielding() const override;

		std::unique_ptr<QAbstractTransition> transitionToIdling() const override;

	public slots:
		virtual void requestUpdate() = 0;

	signals:
		void intervalChanged();

		void schemaChanged();

		void busyChanged();

	protected slots:
		virtual void confirmUpdateFinished() = 0;

	protected:
		Q_SIGNAL void broke();

		Q_SIGNAL void started();

		Q_SIGNAL void stopped();

		Q_SIGNAL void databaseConnected();

		Q_SIGNAL void schemaValidated();

		Q_SIGNAL void updateTimerStarted();

		Q_SIGNAL void updateTimerStopped();

		Q_SIGNAL void updateFinished();


	private slots:
		void onSchemaValidated(bool result);

		void startUpdateTimer();

		void stopUpdateTimer();

	private:
		std::unique_ptr<services::Serviceable::ServiceStatuses> configureStartingOrRepairing(QState * parent);

		struct Members {
			Schema * schema;
			int interval;
			QTimer updateTimer;

			Members():
				schema(nullptr),
				interval(INITIAL_INTERVAL)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020-2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
