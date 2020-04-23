#ifndef DATABASETHREADDICTIONARY_HPP
#define DATABASETHREADDICTIONARY_HPP

#include <cutehmi/Singleton.hpp>

#include <QHash>
#include <QSet>

class QThread;

namespace cutehmi {
namespace shareddatabase {
namespace internal {

class DatabaseDictionary:
	public QObject,
	public Singleton<DatabaseDictionary>
{
		Q_OBJECT

		friend class Singleton<DatabaseDictionary>;

	public:
		void associateThread(const QString & connectionName, QThread * associatedThread);

		int dissociateThread(const QString & connectionName);

		QThread * associatedThread(const QString & connectionName) const;

		void addConnected(const QString & connectionName);

		void removeConnected(const QString & connectionName);

		bool isConnected(const QString & connectionName) const;

		void addManaged(const QString & connectionName);

		void removeManaged(const QString & connectionName);

		bool isManaged(const QString & connectionName) const;

	protected:
		DatabaseDictionary();

	signals:
		void threadChanged(QString connectionName);

	private:
		typedef QHash<QString, QThread *> ThreadsContainer;
		typedef QSet<QString> ConnectedContainer;
		typedef QSet<QString> ManagedContainer;

		struct Members {
			ThreadsContainer threads;
			ConnectedContainer connected;
			ManagedContainer managed;
		};

		MPtr<Members> m;
};

}
}
}

#endif // DATABASETHREADDICTIONARY_HPP
