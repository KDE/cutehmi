#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_1_INCLUDE_CUTEHMI_SHAREDDATABASE_DATABASEWORKER_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_1_INCLUDE_CUTEHMI_SHAREDDATABASE_DATABASEWORKER_HPP

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
		 * @param db databse connection to be used by the worker.
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
		 * Worker went on a strike action. This signal is emitted when worker refused to do the job.
		 */
		void refused(const QString & reason);

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

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
