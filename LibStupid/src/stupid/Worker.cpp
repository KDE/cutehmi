#include "Worker.hpp"

#include <QCoreApplication>

namespace cutehmi {
namespace stupid {

Worker::Worker(std::function<void()> task):
	m_ready(false),
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
	// This acts as a foolproof synchronization mechanism that prevents deletion before object finishes processing WorkEvent.
	m_workMutex.lock();
	m_workMutex.unlock();	// Mutex should be unlocked before it is deleted.
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
	m_readyMutex.lock();
	if (!m_ready)
		// wait() uses internal mechanisms to prevent wakeAll() from waking up threads after m_waitMutex is locked.
		m_waitCondition.wait(& m_readyMutex);
	m_readyMutex.unlock();
}

bool Worker::isReady() const
{
	QMutexLocker m_locker(& m_readyMutex);
	return m_ready;
}

void Worker::employ(QThread & thread, bool start)
{
	moveToThread(& thread);
	if (start)
		work();
}

void Worker::work()
{
	m_workMutex.lock();
	QCoreApplication::postEvent(this, new WorkEvent);
}

bool Worker::event(QEvent * event)
{
	if (event->type() == WorkEvent::RegisteredType()) {
		job();
		m_readyMutex.lock();
		m_ready = true;
		emit ready();
		m_waitCondition.wakeAll();
		m_readyMutex.unlock();

//<principle id="cutehmi.stupid.AbstractWorker.event-memberAccessForbidden">
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
