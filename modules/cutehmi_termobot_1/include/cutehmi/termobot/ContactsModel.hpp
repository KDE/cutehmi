#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_CONTACTSMODEL_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_CONTACTSMODEL_HPP

#include "internal/common.hpp"

#include "../../../src/cutehmi/termobot/DatabaseThread.hpp"

#include <QAbstractListModel>

#include <functional>

namespace cutehmi {
namespace termobot {

//ContactsModel_ReadWorker


class CUTEHMI_TERMOBOT_API ContactsModel:
    public QAbstractListModel
{
	Q_OBJECT

	public:
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

		ContactsModel(DatabaseThread * databaseThread);

		~ContactsModel();

		bool busy() const;

//      read implementation
		QVariant data(const QModelIndex &index, int role) const override;

		int rowCount(const QModelIndex &parent) const override;

		bool removeRows(int row, int count, const QModelIndex &parent) override;

        QHash<int, QByteArray> roleNames() const override;

	signals:
		void busyChanged();

    private:		
		enum Role : int {
			Nick = Qt::UserRole,
			FirstName,
			LastName,
			Active
		};

		struct ContactTuple
		{
				QString nick;
				QString firstName;
				QString lastName;
				bool enabled;
		};

		typedef QList<ContactTuple> ContactsContainer;

		class ReadWorker:
				public Worker
		{
			public:
				ReadWorker(DatabaseThread & DatabaseThread);

				void job() override;

				const ContactsContainer & contacts() const;

			private:
				QString m_connectionName;
				ContactsContainer m_contacts;
		};

		class WorkingCounter
		{
			public:
				WorkingCounter(std::function<void()> busyChanged);

				WorkingCounter & operator ++();

				WorkingCounter & operator --();

				operator bool() const;

			private:
				std::function<void()> m_busyChanged;
				int m_counter;
		};

        struct Members
        {
            QHash<int, QByteArray> roleNames;
			DatabaseThread * databaseThread;
			ContactsContainer contactsContainer;
			mutable ReadWorker readWorker;
			mutable WorkingCounter workingCounter;
        };

		MPtr<Members> m;
};

}
}



#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
