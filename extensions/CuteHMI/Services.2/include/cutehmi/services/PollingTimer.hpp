#ifndef INCLUDECUTEHMISERVICESPOLLINGCONTROLLER_HPP
#define INCLUDECUTEHMISERVICESPOLLINGCONTROLLER_HPP

#include "internal/common.hpp"

#include <QObject>

namespace cutehmi {
namespace services {

/**
 * Polling timer. Polling timer is a simple, single-shot timer, useful when dealing with polling. It allows for dynamic
 * creation of subtimers, which may be used to control execution of individual tasks into which polling process can be decomposed.
 */
class CUTEHMI_SERVICES_API PollingTimer:
	public QObject
{
		Q_OBJECT

	public:
		static constexpr int INITIAL_INTERVAL = 250;
		static constexpr int INITIAL_SUBTIMER_INTERVAL = 10;

		Q_PROPERTY(int interval READ interval WRITE setlInterval NOTIFY intervalChanged)
		Q_PROPERTY(PollingTimer * subtimer READ subtimer CONSTANT)

		explicit PollingTimer(int interval = INITIAL_INTERVAL, QObject * parent = nullptr);

		int interval() const;

		void setlInterval(int interval);

		/**
		 * Get subtimer. Subtimers are created dynamically, whenever some piece of code wants to access it.
		 * @return subtimer.
		 */
		PollingTimer * subtimer();

	public slots:
		/**
		 * Start timer.
		 */
		void start();

	signals:
		void intervalChanged();

		void triggered();

	private slots:
		void shoot();

	private:
		struct Members {
			int interval;
			PollingTimer * subtimer;
		};

		MPtr<Members> m;
};

}
}

#endif // INCLUDECUTEHMISERVICESPOLLINGCONTROLLER_HPP
