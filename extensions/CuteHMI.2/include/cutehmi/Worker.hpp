#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_WORKER_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_WORKER_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QEvent>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

#include <functional>

namespace cutehmi {

/**
 * %Worker. This class acts as a container that allows specified code to be run in a specified thread. This class is useful when
 * dealing with databases, because Qt SQL module does not allow for sharing database connections across threads. Thus if SQL
 * connection is established in dedicated thread, a worker can run a task in that thread and send ready() signal when the task is
 * finished.
 */
class CUTEHMI_API Worker:
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
		 * Constructor. This constructor acts as if @ref employ(QThread &, bool) "employ(@a thread, false)" was called immediately
		 * after constructing default worker object.
		 * @param thread thread in which worker's job should be run.
		 */
		Worker(QThread & thread);

		~Worker() override;

		/**
		 * Get task.
		 * @return task function. See job().
		 */
		std::function<void()> task() const;

		/**
		 * Set task.
		 * @param task task function. See job().
		 */
		void setTask(std::function<void()> task);

		/**
		 * Wait for the worker. Causes calling thread to wait until worker finishes its job. Function does not block until work()
		 * has been called. It also won't block if worker has already finished its job.
		 *
		 * @threadsafe
		 */
		void wait() const;

		/**
		 * Check if worker is ready.
		 * @return @p true when worker has completed the job, @p false
		 * otherwise.
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
		 * Employ worker. Employs worker in another thread. Internally this function moves worker object to the specified thread.
		 * This function imposes same restrictions as QObject::moveToThread().
		 * @param thread thread in which worker's job should be run.
		 * @param start start work. If start is set to @p true, then work() is called immediately.
		 */
		void employ(QThread & thread, bool start = true);

		/**
		 * Do work. This function posts WorkEvent, which tells worker to process the job() inside the thread in which it is
		 * employed.
		 *
		 * @threadsafe
		 */
		void work();

	signals:
		/**
		 * Results are ready. This signal is emitted when the job() has been completed and the results are ready.
		 */
		void ready();

	protected:
		/**
		 * Work event. This class is provided to interact with Worker through Qt event system.
		 */
		class WorkEvent:
			public QEvent
		{
			public:
				/**
				 * Registered event type.
				 * @return value of a QEvent::Type registered for events of this
				 * class.
				 */
				static Type RegisteredType() noexcept;

			public:
				/**
				 * Default constructor.
				 */
				WorkEvent();
		};

		/**
		 * %Worker's job. This function is called when worker receives WorkEvent event. Use employ() function to run job in a
		 * specified thread. This function can be reimplemented. Default implementation calls @a task function if it has been set
		 * (it can be passed to the \ref Worker(std::function<void()>) "constructor" or set via setTask() function). Default
		 * implementation does nothing if @a task has not been set (i.e. @a task = @p nullptr).
		 */
		virtual void job();

		bool event(QEvent * event) override;

	private:
		enum class State {
			UNEMPLOYED,
			EMPLOYED,
			WORKING,
			READY
		};

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

		MPtr<Members> m;
};

}

#endif

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
