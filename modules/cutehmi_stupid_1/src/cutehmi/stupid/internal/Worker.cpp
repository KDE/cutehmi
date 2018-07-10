#include "../../../../include/cutehmi/stupid/internal/Worker.hpp"

#include <QCoreApplication>

namespace cutehmi {
namespace stupid {
namespace internal {

Worker::Worker(std::function<void()> task):
	m(new Members(task))
{
}

Worker::Worker(QThread & thread):
	Worker()
{
	employ(thread, false);
}

Worker::~Worker()
{
	// This acts as a failproof synchronization mechanism that prevents deletion before object finishes processing WorkEvent.
	m->workMutex.lock();
	m->workMutex.unlock();	// Mutex should be unlocked before it gets deleted.
}

void Worker::setTask(std::function<void()> task)
{
	m->task = task;
}

void Worker::job()
{
	if (m->task)
		m->task();
}

void Worker::wait() const
{
	m->stateMutex.lock();
	if (m->state == State::WORKING)
		// wait() uses internal mechanisms to prevent wakeAll() from waking up threads after m->stateMutex is locked.
		m->waitCondition.wait(& m->stateMutex);
	m->stateMutex.unlock();
}

bool Worker::isReady() const
{
	QMutexLocker locker(& m->stateMutex);
	return m->state == State::READY;
}

bool Worker::isWorking() const
{
	QMutexLocker locker(& m->stateMutex);
	return m->state == State::WORKING;
}

void Worker::employ(QThread & thread, bool start)
{
	moveToThread(& thread);
	m->state = State::EMPLOYED;
	if (start)
		work();
}

void Worker::work()
{
	m->workMutex.lock();
	m->stateMutex.lock();
	m->state = State::WORKING;
	m->stateMutex.unlock();
	QCoreApplication::postEvent(this, new WorkEvent);
}

bool Worker::event(QEvent * event)
{
	if (event->type() == WorkEvent::RegisteredType()) {
		job();
		m->stateMutex.lock();
		m->state = State::READY;
		emit ready();
		m->waitCondition.wakeAll();
		m->stateMutex.unlock();

//<principle id="cutehmi::stupid::AbstractWorker-event.member_access_forbidden">
// After unlocking m->workMutex object may be deleted from its former thread.
// From now on members of worker object must not be accessed from within itself or undefined behaviour will occur.
		m->workMutex.unlock();
		return true;
//</principle>
	}

	return Parent::event(event);
}

QEvent::Type Worker::WorkEvent::RegisteredType() noexcept
{
	static const QEvent::Type type = static_cast<QEvent::Type>(QEvent::registerEventType());
	return type;
}

Worker::WorkEvent::WorkEvent():
	QEvent(RegisteredType())
{
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
