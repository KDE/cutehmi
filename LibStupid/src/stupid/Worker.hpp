#ifndef WORKER_H
#define WORKER_H

#include "../platform.hpp"

#include <QObject>
#include <QEvent>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

#include <functional>

namespace cutehmi {
namespace stupid {

/**
 * Worker. This class acts as a container that allows specified code to be run in a specified thread.
 */
class CUTEHMI_STUPID_API Worker:
		public QObject
{
	typedef QObject Parent;

	Q_OBJECT

	public:
		/**
		 * Constructor.
		 * @param task task function. See job().
		 */
		Worker(std::function<void()> task = nullptr);

		/**
		 * Constructor.
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
		 * task function (it can be passed to the constructor or set via setTask()) if it has been set.
		 */
		virtual void job();

		/**
		 * Wait for the worker. Causes calling thread to wait until worker finishes its job.
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
		 * Employ worker. Employs worker in another thread. Internally this function moves worker object
		 * to the specified thread.
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
		bool m_ready;
		std::function<void()> m_task;
		mutable QMutex m_readyMutex;
		mutable QWaitCondition m_waitCondition;
		mutable QMutex m_workMutex;
};

}
}

#endif
