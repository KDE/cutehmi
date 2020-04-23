#ifndef DATAOBJECT_HPP
#define DATAOBJECT_HPP

#include "internal/common.hpp"

#include <cutehmi/InplaceError.hpp>
#include <cutehmi/shareddatabase/DatabaseWorker.hpp>

#include <QObject>
#include <QVector>
#include <QSqlQuery>
#include <QSqlError>
#include <QMutex>

namespace cutehmi {
namespace dataacquisition {

/**
 * Database object.
 */
class CUTEHMI_DATAACQUISITION_API DataObject:
	public QObject
{
		Q_OBJECT

	public:
		/**
		  Database connection name.
		  */
		Q_PROPERTY(QString connectionName READ connectionName WRITE setConnectionName RESET resetConnectionName NOTIFY connectionNameChanged)

		/**
		  Indicates that object is busy processing SQL request.
		  */
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

		DataObject(QObject * parent = nullptr);

		QString connectionName() const;

		void setConnectionName(const QString & connectionName);

		void resetConnectionName();

		bool busy() const;

	signals:
		void connectionNameChanged();

		void busyChanged();

		void errored(cutehmi::InplaceError error);

	protected:
		/**
		 * Push SQL error.
		 * @param sqlError SQL error.
		 *
		 * @threadsafe
		 */
		void pushError(const QSqlError & sqlError);

		/**
		 * Create database worker and assign it a task. Worker ready() signal is connected to processErrors() slot. Each worker is
		 * also connected to incrementBusy() and decrementBusy() slots to reflect its status within @a busy property.
		 * @param task task to be assigned to the worker.
		 * @return worker worker which is assigned to the task.
		 *
		 * @warning worker will be scheduled for deletion after it completes the task (i.e. it emits ready() signal). However if
		 * worker is not ordered to \ref shareddatabase::DatabaseWorker::work() "work" the caller is responsible for deleting it.
		 */
		shareddatabase::DatabaseWorker * worker(std::function<void(QSqlDatabase & db)> task) const;

	protected slots:
		/**
		 * Increment busy counter.
		 */
		void incrementBusy();

		/**
		 * Decrement busy counter.
		 */
		void decrementBusy();

		/**
		 * Process SQL errors. Call this function periodically (e.g. after database worker has done its job) to flush errors
		 * accumulated with pushError() function. Function emits errored() signal on each encountered error.
		 *
		 * @threadsafe
		 */
		virtual void processErrors();

		/**
		 * Print error. This slot is connected to errored() signal by default.
		 * @param error error to be printed. Error is printed using logging macros.
		 */
		void printError(cutehmi::InplaceError error) const;

	private slots:
		void onDatabaseWorkerStriked(const QString & reason);

	private:
		typedef QVector<QSqlError> SQLErrorsContainer;

		struct Members
		{
			QString connectionName;
			mutable QMutex sqlErrorsMutex;
			SQLErrorsContainer sqlErrors;
			int busy;

			Members():
				busy(0)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // DATAOBJECT_HPP
