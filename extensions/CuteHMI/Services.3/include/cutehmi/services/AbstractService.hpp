#ifndef ABSTRACTSERVICE_HPP
#define ABSTRACTSERVICE_HPP

#include "internal/common.hpp"
#include "StateInterface.hpp"

//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
#include <cutehmi/workarounds/qt5compatibility/qsizetype.hpp>
//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

#include <QObject>
#include <QString>
#include <QStateMachine>
#include <QTimer>
#include <QQmlEngine>
#include <QQmlListProperty>

namespace cutehmi {
namespace services {

class AbstractServiceController;

/**
 * Abstract service.
 *
 * Guarantee is given that @ref states property is never @a nullptr, nor any of its states is ever @p nullptr, though it is allowed
 * that individual states can change. Subclasses have to take care to ensure that this guarantee is not violated. Additionaly they
 * should take care about initialized() signal, which should be emitted once the service has been initialized and it's ready to be
 * started. It is also well-seen if subclasses update service @a status accordingly to the service state during its lifecycle.
 */
class CUTEHMI_SERVICES_API AbstractService:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(AbstractService)
		QML_UNCREATABLE("AbstractService is an abstract class")

	public:
		static constexpr int INITIAL_STOP_TIMEOUT = 30000;

		static constexpr int INITIAL_START_TIMEOUT = 30000;

		static constexpr int INITIAL_REPAIR_TIMEOUT = 30000;

		static constexpr const char * INITIAL_NAME = "Unnamed Service";

		Q_PROPERTY(int stopTimeout READ stopTimeout WRITE setStopTimeout NOTIFY stopTimeoutChanged)

		Q_PROPERTY(int startTimeout READ startTimeout WRITE setStartTimeout NOTIFY startTimeoutChanged)

		Q_PROPERTY(int repairTimeout READ repairTimeout WRITE setRepairTimeout NOTIFY repairTimeoutChanged)

		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

		Q_PROPERTY(QString status READ status NOTIFY statusChanged)

		Q_PROPERTY(cutehmi::services::StateInterface * states READ states CONSTANT)

		Q_PROPERTY(QQmlListProperty<cutehmi::services::AbstractServiceController> defaultControllers READ defaultControllerList CONSTANT)

		Q_PROPERTY(QQmlListProperty<cutehmi::services::AbstractServiceController> controllers READ controllerList CONSTANT)

		~AbstractService() override;

		int stopTimeout() const;

		/**
		 * Set stop timeout.
		 * @param stopTimeout amount of time [milliseconds] after which stopping or evacuating sequence should be interrupted.
		 * Setting a negative value will disable timeout functionality.
		 */
		void setStopTimeout(int stopTimeout);

		int startTimeout() const;

		/**
		 * Set start timeout.
		 * @param startTimeout amount of time [milliseconds] after which starting sequence should be interrupted. Setting a negative
		 * value will disable timeout functionality.
		 */
		void setStartTimeout(int startTimeout);

		int repairTimeout() const;

		/**
		 * Set repair timeout.
		 * @param repairTimeout amount of time [milliseconds] after which repair sequence should be interrupted. Setting a negative
		 * value will disable timeout functionality.
		 */
		void setRepairTimeout(int repairTimeout);

		QString name() const;

		void setName(const QString & name);

		QString status() const;

		/**
		 * Get state interface.
		 *
		 * This is the object passed to the constructor as @a stateInterface. The pointer always points to the same object, but its
		 * individual state properties can change.
		 *
		 * @return state interface.
		 */
		cutehmi::services::StateInterface * states() const;

		QQmlListProperty<cutehmi::services::AbstractServiceController> defaultControllerList();

		QQmlListProperty<cutehmi::services::AbstractServiceController> controllerList();

		Q_INVOKABLE void appendController(cutehmi::services::AbstractServiceController * controller);

		Q_INVOKABLE void clearControllers();

	public slots:
		void start();

		void stop();

		void activate();

	signals:
		void stopTimeoutChanged();

		void startTimeoutChanged();

		void repairTimeoutChanged();

		void nameChanged();

		void statusChanged();

		void started();

		void stopped();

		void activated();

		/**
		 * This signal is emitted, when service has performed all the initialization tasks and it is ready to be started. After this
		 * signal has been emitted a service should respond to start() slot.
		 */
		void initialized();

	protected:
		typedef QList<AbstractServiceController *> ControllersContainer;

		/**
		 * Constructor.
		 * @param stateInterface state interface.
		 * @param status initial service status.
		 * @param defaultControllers default controllers.
		 * @param parent parent object.
		 */
		AbstractService(std::unique_ptr<StateInterface> stateInterface, const QString & status, QObject * parent = nullptr, const ControllersContainer * defaultControllers = & DefaultControllers());

		static const ControllersContainer & DefaultControllers();

		const ControllersContainer & controllers() const;

		ControllersContainer & controllers();

	protected slots:
		void setStatus(const QString & status);

	private:
		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType ControllerListCount(QQmlListProperty<AbstractServiceController> * property);

		static AbstractServiceController * ControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		static void ControllerListClear(QQmlListProperty<AbstractServiceController> * property);

		static void ControllerListAppend(QQmlListProperty<AbstractServiceController> * property, AbstractServiceController * value);

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType DefaultControllerListCount(QQmlListProperty<AbstractServiceController> * property);

		static AbstractServiceController * DefaultControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		const ControllersContainer * defaultControllerListData() const;

		struct Members {
			int stopTimeout = INITIAL_STOP_TIMEOUT;
			int startTimeout = INITIAL_START_TIMEOUT;
			int repairTimeout = INITIAL_REPAIR_TIMEOUT;
			QString name = INITIAL_NAME;
			QString status;
			StateInterface * stateInterface;
			ControllersContainer controllers;
			QQmlListProperty<AbstractServiceController> controllerList;
			QQmlListProperty<AbstractServiceController> defaultControllerList;

			Members(AbstractService * p_parent, StateInterface * p_stateInterface, const QString & p_status, const ControllersContainer * p_defaultControllers):
				status(p_status),
				stateInterface(p_stateInterface),
				controllerList(p_parent, & controllers, & AbstractService::ControllerListAppend, & AbstractService::ControllerListCount, & AbstractService::ControllerListAt, & AbstractService::ControllerListClear),
				defaultControllerList(p_parent, const_cast<ControllersContainer *>(p_defaultControllers), & AbstractService::DefaultControllerListCount, & AbstractService::DefaultControllerListAt)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // ABSTRACTSERVICE_HPP
