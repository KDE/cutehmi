#include <cutehmi/shareddatabase/internal/DatabaseThread.hpp>

namespace cutehmi {
namespace shareddatabase {
namespace internal {

DatabaseThread::DatabaseThread(QObject * parent):
	QThread(parent),
	m(new Members)
{
}

void DatabaseThread::start(std::unique_ptr<DatabaseConnectionHandler> handler)
{
	m->handler = std::move(handler);
	if (m->handler->thread() != this)
		m->handler->moveToThread(this);
	QThread::start();
}

void DatabaseThread::run()
{
	m->handler->connect();
	exec();
	m->handler->disconnect();
	m->handler.reset();
}

}
}
}
