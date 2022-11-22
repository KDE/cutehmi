#ifndef CUTEHMI_SERVICES_SERVICEDEPENDENCY_HPP
#define CUTEHMI_SERVICES_SERVICEDEPENDENCY_HPP

#include "internal/common.hpp"
#include "ServiceGroupRule.hpp"

//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
#include <cutehmi/workarounds/qt5compatibility/qsizetype.hpp>
//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

#include <QPointer>
#include <QSignalTransition>
#include <QQmlEngine>
#include <QQmlListProperty>

namespace cutehmi {
namespace services {

class AbstractService;

class CUTEHMI_SERVICES_API ServiceDependency:
	public ServiceGroupRule
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceDependency)

	public:
		Q_PROPERTY(cutehmi::services::AbstractService * service READ service WRITE setService NOTIFY serviceChanged)

		Q_PROPERTY(QQmlListProperty<cutehmi::services::AbstractService> requires READ requiredServiceList CONSTANT)

		ServiceDependency(QObject * parent = nullptr);

		void setService(AbstractService * service);

		cutehmi::services::AbstractService * service() const;

		QQmlListProperty<cutehmi::services::AbstractService> requiredServiceList();

		Q_INVOKABLE void appendRequiredService(cutehmi::services::AbstractService * service);

		Q_INVOKABLE void clearRequiredServices();

		std::unique_ptr<QAbstractTransition> conditionalTransition(SlotType type, const AbstractService * service) override;

	signals:
		void serviceChanged();

	protected:
		typedef QList<AbstractService *> RequiredServicesContainer;

		const RequiredServicesContainer & requiredServices() const;

		RequiredServicesContainer & requiredServices();

	private:
		class StartConditionTransition: public QSignalTransition {
			public:
				StartConditionTransition(QPointer<ServiceDependency> serviceDependency);

			protected:
				bool test() const;

				bool eventTest(QEvent * event) override;

			private:
				void reconnectStateEntered();

				struct Members {
					QPointer<ServiceDependency> serviceDependency;
					QList<QMetaObject::Connection> stateEnteredConnections;
				};

				MPtr<Members> m;
		};

		class StopConditionTransition: public QSignalTransition {
			public:
				StopConditionTransition(QPointer<ServiceDependency> serviceDependency);

			protected:
				bool test() const;

				bool eventTest(QEvent * event) override;

			private:
				void reconnectStateEntered();

				struct Members {
					QPointer<ServiceDependency> serviceDependency;
					QMetaObject::Connection stoppedEnteredConnection;
					QMetaObject::Connection interruptedEnteredConnection;
				};

				MPtr<Members> m;
		};

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType RequiredServiceListCount(QQmlListProperty<AbstractService> * property);

		static AbstractService * RequiredServiceListAt(QQmlListProperty<AbstractService> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		static void RequiredServiceListClear(QQmlListProperty<AbstractService> * property);

		static void RequiredServiceListAppend(QQmlListProperty<AbstractService> * property, AbstractService * value);

		struct Members
		{
			AbstractService * service = nullptr;
			RequiredServicesContainer requiredServices;
			QQmlListProperty<AbstractService> requiredServiceList;

			Members(ServiceDependency * p_parent):
				requiredServiceList(p_parent, & requiredServices, & ServiceDependency::RequiredServiceListAppend, & ServiceDependency::RequiredServiceListCount, & ServiceDependency::RequiredServiceListAt, & ServiceDependency::RequiredServiceListClear)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif
