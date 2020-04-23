#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_RECENCYWRITER_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_RECENCYWRITER_HPP

#include "internal/common.hpp"
#include "internal/RecencyCollective.hpp"
#include "AbstractWriter.hpp"

#include <cutehmi/services/Serviceable.hpp>

#include <QTimer>

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API RecencyWriter:
	public AbstractWriter
{
		Q_OBJECT

	public:
		static constexpr int INITIAL_INTERVAL = 1000;

		/**
		  Interval [ms] between samples.

		  @assumption{cutehmi::dataacquisition::History-interval_non_negative}
		  Value of @a interval property should be non-negative.
		  */
		Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

		RecencyWriter(QObject * parent = nullptr);

		int interval() const;

		void setInterval(int interval);

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

	signals:
		void intervalChanged();

	CUTEHMI_PROTECTED_SIGNALS:
		void updateTimerStarted();

		void updateTimerStopped();

	private slots:
		void updateValues();

		void onSchemaChanged();

		void startUpdateTimer();

		void stopUpdateTimer();

	private:
		std::unique_ptr<services::Serviceable::ServiceStatuses> configureStartingOrRepairing(QState * parent);

		struct Members
		{
			internal::RecencyCollective dbCollective;
			QTimer updateTimer;
			int interval;

			Members():
				interval(INITIAL_INTERVAL)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif
