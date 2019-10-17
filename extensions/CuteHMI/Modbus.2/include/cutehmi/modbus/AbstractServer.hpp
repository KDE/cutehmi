#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTSERVER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTSERVER_HPP

#include "AbstractDevice.hpp"

namespace cutehmi {
namespace modbus {

/**
 * Abstract server.
 *
 * @remark Server is always ready to handle requests, even if it is not in opened state (i.e. it does not listen for clients),
 * because requests are affecting server internal state.
 */
class CUTEHMI_MODBUS_API AbstractServer:
	public AbstractDevice
{
		Q_OBJECT

	public:
		static constexpr bool INITIAL_BUSY = false;

		Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

		bool busy() const;

		virtual void setBusy(bool busy) = 0;

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
		void busyChanged();

	protected:
		AbstractServer(QObject * parent = nullptr);

		void handleRequest(const QJsonObject & request) override;

	protected slots:
		virtual void handleCoilsWritten(quint16 address, quint16 amount);

		virtual void handleDiscreteInputsWritten(quint16 address, quint16 amount);

		virtual void handleHoldingRegistersWritten(quint16 address, quint16 amount);

		virtual void handleInputRegistersWritten(quint16 address, quint16 amount);

		void updateBusy(bool busy);

	CUTEHMI_PROTECTED_SIGNALS:
		void requestReceived(QJsonObject request);

		void broke();

		void stopped();

		void started();

	private:
		struct Members {
			bool busy = INITIAL_BUSY;
		};

		MPtr<Members> m;
};

}
}

#endif
