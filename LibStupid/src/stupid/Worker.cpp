#include "../../include/stupid/Worker.hpp"

#include <QCoreApplication>

namespace cutehmi {
namespace stupid {

Worker::Worker(std::function<void()> task):
	m_state(State::UNEMPLOYED),
	m_task(task)
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
	m_workMutex.lock();
	m_workMutex.unlock();	// Mutex should be unlocked before it gets deleted.
}

void Worker::setTask(std::function<void()> task)
{
	m_task = task;
}

void Worker::job()
{
	if (m_task)
		m_task();
}

void Worker::wait() const
{
	m_stateMutex.lock();
	if (m_state == State::WORKING)
		// wait() uses internal mechanisms to prevent wakeAll() from waking up threads after m_stateMutex is locked.
		m_waitCondition.wait(& m_stateMutex);
	m_stateMutex.unlock();
}

bool Worker::isReady() const
{
	QMutexLocker locker(& m_stateMutex);
	return m_state == State::READY;
}

bool Worker::isWorking() const
{
	QMutexLocker locker(& m_stateMutex);
	return m_state == State::WORKING;
}

void Worker::employ(QThread & thread, bool start)
{
	moveToThread(& thread);
	m_state = State::EMPLOYED;
	if (start)
		work();
}

void Worker::work()
{
	m_workMutex.lock();
	m_stateMutex.lock();
	m_state = State::WORKING;
	m_stateMutex.unlock();
	QCoreApplication::postEvent(this, new WorkEvent);
}

bool Worker::event(QEvent * event)
{
	if (event->type() == WorkEvent::RegisteredType()) {
		job();
		m_stateMutex.lock();
		m_state = State::READY;
		emit ready();
		m_waitCondition.wakeAll();
		m_stateMutex.unlock();

//<principle id="cutehmi.stupid.AbstractWorker.event.member_access_forbidden">
// After unlocking m_workMutex object may be deleted from its former thread.
// From now on members of worker object must not be accessed from within itself or undefined behaviour will occur.
		m_workMutex.unlock();
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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
