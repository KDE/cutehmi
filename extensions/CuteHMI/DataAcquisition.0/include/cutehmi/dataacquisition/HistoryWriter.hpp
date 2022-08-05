#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_HISTORYWRITER_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_HISTORYWRITER_HPP

#include "internal/HistoryCollective.hpp"
#include "internal/DbServiceableMixin.hpp"
#include "AbstractWriter.hpp"

#include <cutehmi/services/Serviceable.hpp>

#include <QTimer>

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API HistoryWriter:
	public AbstractWriter,
	private internal::DbServiceableMixin<HistoryWriter>
{
		Q_OBJECT
		QML_NAMED_ELEMENT(HistoryWriter)

		friend class internal::DbServiceableMixin<HistoryWriter>;

	public:
		static constexpr int INITIAL_INTERVAL = 100;
		static constexpr int INITIAL_SAMPLES = 100;

		/**
		  Interval [ms] between samples.

		  @assumption{cutehmi::dataacquisition::History-interval_non_negative}
		  Value of @a interval property should be non-negative.
		  */
		Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

		/**
		  Number of samples per candle to be stored in the database.

		  @assumption{cutehmi::dataacquisition::History-samples_greater_than_zero}
		  Value of @a samples property should be greater than zero.
		  */
		Q_PROPERTY(int samples READ samples WRITE setSamples NOTIFY samplesChanged)

		HistoryWriter(QObject * parent = nullptr);

		int interval() const;

		void setInterval(int interval);

		int samples() const;

		void setSamples(int samples);

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

	signals:
		void intervalChanged();

		void samplesChanged();

	protected slots:
		void sampleValues();

		void insertValues();

	protected:
		Q_SIGNAL void initialized();

		Q_SIGNAL void samplingTimerStarted();

		Q_SIGNAL void samplingTimerStopped();

		Q_SIGNAL void schemaValidatedTrue();

		Q_SIGNAL void schemaValidatedFalse();

		Q_SIGNAL void insertValuesBegan();

		Q_SIGNAL void collectiveFinished();

	private slots:
		void onSchemaChanged();

		void initialize();

		void adjustSamplingTimer();

		void startSamplingTimer();

		void stopSamplingTimer();

		void confirmCollectiveFinished();

	private:
		std::unique_ptr<ServiceStatuses> configureStartingOrRepairing(QState * parent);

		void clearData();

		template <typename T>
		void addSample(T value, internal::HistoryCollective::Tuple & tuple);

		struct Members
		{
			internal::HistoryCollective::TuplesContainer tuples;
			internal::HistoryCollective dbCollective;
			QTimer samplingTimer;
			int interval;
			int samples;
			int sampleCounter;

			Members():
				interval(INITIAL_INTERVAL),
				samples(INITIAL_SAMPLES),
				sampleCounter(0)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
