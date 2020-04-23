#ifndef DATABASEWORKER_HPP
#define DATABASEWORKER_HPP

#include "internal/common.hpp"

#include <cutehmi/Worker.hpp>

#include <QSqlDatabase>

namespace cutehmi {
namespace shareddatabase {

/**
 * %Database worker. Convenient worker class that runs tasks in the same thread as where database connection lives.
 */
class CUTEHMI_SHAREDDATABASE_API DatabaseWorker:
	public QObject
{
		Q_OBJECT

	public:
		/**
		 * Constructor. This constructor employs the worker in the same thread as where database connection denoted by
		 * @a connectionName lives.
		 * @param connectionName database connection name.
		 * @param task task function. See job().
		 */
		explicit DatabaseWorker(const QString & connectionName, std::function<void(QSqlDatabase & db)> task = nullptr);

		/**
		 * Set task.
		 * @param task task function. See job().
		 */
		void setTask(std::function<void(QSqlDatabase & db)> task);

		/**
		 * %Worker's job. This function can be reimplemented. Default implementation calls @a task function if it has been set (it
		 * can be passed to the \ref DatabseWorker(const QString & connectionName, std::function<void(QSqlDatabase & db)> task)
		 * "constructor" or set via setTask() function). Default implementation does nothing if @a task has not been set (i.e.
		 * @a task = @p nullptr).
		 * @paragraph db databse connection to be used by the worker.
		 */
		virtual void job(QSqlDatabase & db);

		/**
		 * Wait for the worker. Causes calling thread to wait until worker finishes its job. Function does not block until work()
		 * has been called. It also won't block if worker has already finished its job.
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
		 * Do the work. This function tells worker to process the job() in database thread.
		 */
		void work();

	signals:
		/**
		 * Work started. This signal is emitted just before worker starts processing the \ref job(QSqlDatabase & db) "job".
		 */
		void started();

		/**
		 * Results are ready. This signal is emitted when the job() has been completed and the results are ready.
		 */
		void ready();

		/**
		 * Worker performed strike action. This signal is emitted when worker denied to do the job.
		 */
		void striked(const QString & reason);

	protected:
		/**
		 * Get database thread.
		 * @return database thread.
		 */
		QThread * dbThread() const;

		/**
		 * Get database connection.
		 * @return database connection.
		 *
		 * @warning database connection lives inside database thread. This means that this function can not be called from a thread
		 * other than database thread, i.e. it should not be used outside the job() scope.
		 */
		QSqlDatabase * db();

		/**
		 * Get database connection.
		 * @return database connection.
		 *
		 * @warning database connection lives inside database thread. This means that this function can not be called from a thread
		 * other than database thread, i.e. it should not be used outside the job() scope.
		 */
		const QSqlDatabase * db() const;

	private slots:
		void updateDbThread(const QString & connectionName);

	private:
		void instantiateWorker();

		struct Members {
			const QString connectionName;
			std::function<void(QSqlDatabase & db)> task;
			std::unique_ptr<Worker> worker;
			std::unique_ptr<QSqlDatabase> db;
		};

		MPtr<Members> m;
};

}
}

#endif // DATABASEWORKER_HPP
