#ifndef CUTEHMI_CUTEHMI__STUPID__1__LIB_INCLUDE_STUPID_INTERNAL_WORKER_HPP
#define CUTEHMI_CUTEHMI__STUPID__1__LIB_INCLUDE_STUPID_INTERNAL_WORKER_HPP

#include "common.hpp"

#include <QObject>
#include <QEvent>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

#include <functional>

namespace cutehmi {
namespace stupid {
namespace internal {

/**
 * Worker. This class acts as a container that allows specified code to be run in a specified thread.
 *
 * @obsolete replaced by cutehmi::base::Worker.
 */
class Worker:
	public QObject
{
	typedef QObject Parent;

	Q_OBJECT

	public:
		/**
		 * Default constructor.
		 * @param task task function. See job().
		 */
		Worker(std::function<void()> task = nullptr);

		/**
		 * Constructor. This constructor acts as if employ(@a thread, false) was called immediately after
		 * constructing default worker object.
		 * @param thread thread in which worker's job should be run.
		 */
		Worker(QThread & thread);

		~Worker() override;

		/**
		 * Set task.
		 * @param task task function. See job().
		 */
		void setTask(std::function<void()> task);

		/**
		 * Worker's job. This function is called when worker receives WorkEvent. Use employ() function to
		 * run job in a specified thread. This function can be reimplemented. Default implementation calls
		 * @a task function (it can be passed to the constructor or set via setTask()), if it has been set.
		 * Default implementation does nothing if @a task has not been set (i.e. @a task = @p nullptr).
		 */
		virtual void job();

		/**
		 * Wait for the worker. Causes calling thread to wait until worker finishes its job. Function
		 * does not block until work() has been called. It also won't block if worker has already
		 * finished its job.
		 *
		 * @threadsafe
		 */
		void wait() const;

		/**
		 * Check if worker is ready.
		 * @return @p true when worker has completed the job, @p false otherwise.
		 *
		 * @threadsafe
		 */
		bool isReady() const;

		/**
		 * Check if worker is working.
		 * @return @p true if worker is processing its job, @p false otherwise.
		 *
		 * @threadsafe
		 */
		bool isWorking() const;

		/**
		 * Employ worker. Employs worker in another thread. Internally this function moves worker object
		 * to the specified thread. This function imposes same restrictions as QObject::moveToThread().
		 * @param thread thread in which worker's job should be run.
		 * @param if start is set to @p true, then work() is called immediately.
		 */
		void employ(QThread & thread, bool start = true);

		/**
		 * Work. This function posts WorkEvent, which tells worker to process the job() inside the thread in which it is employed.
		 *
		 * @threadsafe
		 */
		void work();

	protected:
		enum class State {
			UNEMPLOYED,
			EMPLOYED,
			WORKING,
			READY
		};

		/**
		 * Work event. This class is provided to interact with AbstractWorker through Qt event system.
		 */
		class WorkEvent:
				public QEvent
		{
			public:
				/**
				 * Registered event type.
				 * @return value of a QEvent::Type registered for events of this class.
				 */
				static Type RegisteredType() noexcept;

			public:
				/**
				 * Default constructor.
				 */
				WorkEvent();
		};

		bool event(QEvent * event) override;

	signals:
		/**
		 * Results are ready. This signal is emitted when the job() has been completed and the results are ready.
		 */
		void ready();

	private:
		struct Members
		{
			State state;
			std::function<void()> task;
			mutable QMutex stateMutex;
			mutable QWaitCondition waitCondition;
			mutable QMutex workMutex;

			Members(std::function<void()> p_task):
				state(State::UNEMPLOYED),
				task(p_task)
			{
			}
		};

		utils::MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
