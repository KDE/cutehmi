#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_SRC_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASEDICTIONARY_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_SRC_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASEDICTIONARY_HPP

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

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
