#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_1_INCLUDE_CUTEHMI_SHAREDDATABASE_DATAOBJECT_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_1_INCLUDE_CUTEHMI_SHAREDDATABASE_DATAOBJECT_HPP

#include "internal/common.hpp"
#include "DatabaseWorker.hpp"

#include <cutehmi/InplaceError.hpp>

#include <QObject>
#include <QVector>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMutex>
#include <QQmlEngine>

namespace cutehmi {
namespace shareddatabase {

/**
 * Database object.
 */
class CUTEHMI_SHAREDDATABASE_API DataObject:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(DataObject)
		QML_UNCREATABLE("DataObject can not be created from QML")

	public:
		/**
		  Database connection name.
		  */
		Q_PROPERTY(QString connectionName READ connectionName WRITE setConnectionName RESET resetConnectionName NOTIFY connectionNameChanged)

		/**
		  busy status. Indicates that object is busy processing SQL request.
		  */
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

		/**
		 * Constructor.
		 * @param parent parent object.
		 */
		DataObject(QObject * parent = nullptr);

		/**
		 * Get connection name.
		 * @return connection name.
		 */
		QString connectionName() const;

		/**
		 * Set connection name.
		 * @param connectionName connection name.
		 */
		void setConnectionName(const QString & connectionName);

		/**
		 * Reset connection name.
		 */
		void resetConnectionName();

		/**
		 * Get busy status. Busy status is affected by employed workers, but can be also controlled with incrementBusy() and
		 * decrementBusy() slots.
		 * @return busy status.
		 *
		 * @see incrementBusy(), decrementBusy(), worker().
		 */
		bool busy() const;

	signals:
		/**
		 * Connection name changed. This signal is emitted when connection name has changed.
		 */
		void connectionNameChanged();

		/**
		 * Busy changed. This signal is emitted when busy status has changed.
		 */
		void busyChanged();

		/**
		 * Errored. This signal is emitted when error was encountered.
		 * @param error error.
		 */
		void errored(cutehmi::InplaceError error);

	protected:
		/**
		 * Push SQL error.
		 * @param sqlError SQL error.
		 * @param query query associated with error.
		 *
		 * @threadsafe
		 */
		void pushError(const QSqlError & sqlError, const QString & query = QString());

		/**
		 * Create database worker and assign it a task. Worker ready() signal is connected to processErrors() slot. Each worker is
		 * also connected to incrementBusy() and decrementBusy() slots to reflect its status within @a busy property.
		 * @param task task to be assigned to the worker.
		 * @return worker worker which is assigned to the task.
		 *
		 * @warning worker will be scheduled for deletion after it completes the task (i.e. it emits ready() signal). However if
		 * worker is not ordered to \ref DatabaseWorker::work() "work" the caller is responsible for deleting it.
		 */
		DatabaseWorker * worker(std::function<void(QSqlDatabase & db)> task) const;

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
		void onDatabaseWorkerRefused(const QString & reason);

	private:
		typedef QVector<std::pair<QSqlError, QString>> SQLErrorsContainer;

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

#endif

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
