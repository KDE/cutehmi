#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

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

		Q_PROPERTY(Schema * schema READ schema WRITE setSchema NOTIFY schemaChanged)

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

	CUTEHMI_PROTECTED_SIGNALS:
		void broke();

		void started();

		void stopped();

		void databaseConnected();

		void schemaValidated();

		void updateTimerStarted();

		void updateTimerStopped();

		void updateFinished();


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

#endif // DATAMODEL_HPP
