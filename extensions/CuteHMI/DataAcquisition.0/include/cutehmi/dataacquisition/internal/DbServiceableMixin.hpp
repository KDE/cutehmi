#ifndef SERVICEABLEDATAMIXIN_HPP
#define SERVICEABLEDATAMIXIN_HPP

#include <cutehmi/services/Serviceable.hpp>

#include <cutehmi/shareddatabase/Database.hpp>

#include <QState>
#include <QTimer>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

template <class DERIVED>
class DbServiceableMixin
{
	protected:
		QState * createWaitingForDatabaseConnectedSate(QState * parent, services::Serviceable::ServiceStatuses * statuses = nullptr, QState * target = nullptr);

		QState * createValidatingSchemaSate(QState * parent, services::Serviceable::ServiceStatuses * statuses = nullptr, QState * target = nullptr);

	private:
		const DERIVED & derived() const;

		DERIVED & derived();
};

template <typename DERIVED>
QState * DbServiceableMixin<DERIVED>::createWaitingForDatabaseConnectedSate(QState * parent, services::Serviceable::ServiceStatuses * statuses, QState * target)
{
	QState * state = new QState(parent);
	QObject::connect(state, & QState::entered, & derived(), [this, state]() {
		if (derived().schema()) {
			QTimer * timer = new QTimer(derived().schema());
			QObject::connect(timer, & QTimer::timeout, [this]() {
				if (shareddatabase::Database::IsConnected(derived().schema()->connectionName()))
					emit derived().databaseConnected();
			});
			QObject::connect(state, & QState::exited, timer, & QTimer::stop);
			QObject::connect(state, & QState::exited, timer, & QObject::deleteLater);
			timer->start(250);
		} else {
			CUTEHMI_CRITICAL("Schema is not set for '" << this << "' object.");
			emit derived().broke();
		}
	});

	if (statuses)
		statuses->insert(state, QCoreApplication::translate("cutehmi::dataacquisition::internal::DbServiceableMixin", "Waiting for database"));

	if (target)
		state->addTransition(& derived(), & DERIVED::databaseConnected, target);

	return state;
}

template <typename DERIVED>
QState * DbServiceableMixin<DERIVED>::createValidatingSchemaSate(QState * parent, services::Serviceable::ServiceStatuses * statuses, QState * target)
{
	QState * state = new QState(parent);
	QObject::connect(state, & QState::entered, & derived(), [this]() {
		if (!derived().schema()) {
			CUTEHMI_CRITICAL("Schema is not set for '" << this << "' object.");
			emit derived().broke();
		} else
			derived().schema()->validate();
	});

	if (statuses)
		statuses->insert(state, QCoreApplication::translate("cutehmi::dataacquisition::internal::DbServiceableMixin", "Validating schema"));

	if (target)
		state->addTransition(& derived(), & DERIVED::schemaValidated, target);

	return state;
}

template <typename DERIVED>
const DERIVED & DbServiceableMixin<DERIVED>::derived() const
{
	return static_cast<const DERIVED &>(*this);
}

template <typename DERIVED>
DERIVED & DbServiceableMixin<DERIVED>::derived()
{
	return static_cast<DERIVED &>(*this);
}

}
}
}

#endif // DbServiceableMixin_HPP
