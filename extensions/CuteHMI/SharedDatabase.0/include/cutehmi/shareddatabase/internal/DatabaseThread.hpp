#ifndef DATABASETHREAD_HPP
#define DATABASETHREAD_HPP

#include "common.hpp"
#include "DatabaseConnectionHandler.hpp"

#include <QThread>

namespace cutehmi {
namespace shareddatabase {
namespace internal {

class CUTEHMI_SHAREDDATABASE_PRIVATE DatabaseThread:
	public QThread
{
		Q_OBJECT

	public:
		DatabaseThread(QObject * parent = nullptr);

		void start(std::unique_ptr<DatabaseConnectionHandler> handler);

	protected:
		void run() override;

	private:
		struct Members
		{
			std::unique_ptr<DatabaseConnectionHandler> handler;
		};

		MPtr<Members> m;
};

}
}
}

#endif // DATABASETHREAD_HPP
