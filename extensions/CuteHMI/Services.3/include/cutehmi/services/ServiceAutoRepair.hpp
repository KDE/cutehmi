#ifndef CUTEHMI_SERVICES_SERVICEAUTOREPAIR_HPP
#define CUTEHMI_SERVICES_SERVICEAUTOREPAIR_HPP

#include "internal/common.hpp"

#include "AbstractServiceController.hpp"

#include <QHash>

#include <memory>

class QAbstractState;

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API ServiceAutoRepair:
	public cutehmi::services::AbstractServiceController
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceAutoRepair)

	public:
		static constexpr int INITIAL_INITIAL_INTERVAL = 10000;

		static constexpr const char * INITIAL_INTERVAL_FUNCTION = "(function (previousInterval) { return previousInterval; })";

		Q_PROPERTY(int initialInterval READ initialInterval WRITE setInitialInterval NOTIFY initialIntervalChanged)

		Q_PROPERTY(QJSValue intervalFunction READ intervalFunction WRITE setIntervalFunction NOTIFY intervalFunctionChanged)

		explicit ServiceAutoRepair(QObject * parent = nullptr);

		~ServiceAutoRepair() override;

		QJSValue intervalFunction() const;

		int initialInterval() const;

		void setInitialInterval(int initialInterval);

		void setIntervalFunction(const QJSValue & intervalFunction);

		void setIntervalFunction(const QString & intervalFunction);

		void subscribe(AbstractService * service) override;

		void unsubscribe(AbstractService * service) override;

	signals:
		void initialIntervalChanged();

		void intervalFunctionChanged();

	private:
		struct ServiceEntry {
			QTimer * timer;
			QMetaObject::Connection startingEnteredConnection;
			QMetaObject::Connection startingChangedConnection;
			QMetaObject::Connection startedEnteredConnection;
			QMetaObject::Connection startedChangedConnection;
			QMetaObject::Connection repairingEnteredConnection;
			QMetaObject::Connection repairingChangedConnection;
			QMetaObject::Connection brokenEnteredConnection;
			QMetaObject::Connection brokenChangedConnection;
		};

		typedef QHash<AbstractService *, ServiceEntry *> ServiceDataContainer;

		// Helper engine to evaulate interval strings (QJSEngine related to QJSValue must available when QJSValue::call() is made).
		static QJSEngine & JSEngine();

		QMetaObject::Connection connectResetIntervalOnStateEntered(const QAbstractState * state, QTimer * timer);

		QMetaObject::Connection connectRepairingEntered(const AbstractService * service, QTimer * timer);

		QMetaObject::Connection connectBrokenEntered(const AbstractService * service, QTimer * timer);

		void clearServiceEntry(AbstractService * service);

		struct Members {
			int initialInterval;
			QJSValue intervalFunction;
			ServiceDataContainer serviceData;
		};

		MPtr<Members> m;
};


}
}

#endif
