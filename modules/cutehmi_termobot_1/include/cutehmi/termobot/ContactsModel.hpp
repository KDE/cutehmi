#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_CONTACTSMODEL_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_CONTACTSMODEL_HPP

#include "internal/common.hpp"
#include "internal/WorkingCounter.hpp"

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

		// read implementation
		QVariant data(const QModelIndex & index, int role) const override;

		int rowCount(const QModelIndex & parent) const override;

		// update implementation
		Q_INVOKABLE bool update(const QString & nick, const QString & newNick, const QString & newFirstName, const QString & lastName, const bool & newActive);

//		bool setData(const QModelIndex & index, const QVariant & value, int role) override;

		Qt::ItemFlags flags(const QModelIndex & index) const override;

		// delete implementation
		Q_INVOKABLE bool remove(QString nick);

		// create implementation
		Q_INVOKABLE bool insert(QString nick, QString firstName, QString lastName, bool enabled);

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

		class CreateWorker:
				public Worker
		{
			public:
				CreateWorker(DatabaseThread & databaseThread);

				void job() override;

				void contact(std::unique_ptr<ContactTuple> newContact);

			private:
				QString m_connectionName;
				std::unique_ptr<ContactTuple> m_contact;
		};

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

		class UpdateWorker:
				public Worker
		{
			public:
				UpdateWorker(DatabaseThread & databaseThread);

				void job() override;

				const ContactTuple & contact() const;

				void contact(std::unique_ptr<ContactTuple> newContact);

				void nick(const QString & newNick);

				const int & changedRow() const;

				void changedRow(const int & newRow);

			private:
				int m_changedRow;
				QString m_connectionName;
				QString m_nick;
				std::unique_ptr<ContactTuple> m_contact;
		};

		class DeleteWorker:
				public Worker
		{
			public:
				DeleteWorker(DatabaseThread & databaseThread);

				void job() override;

				void nick(const QString & newNick);

			private:
				QString m_connectionName;
				QString m_nick;
		};

        struct Members
        {
			bool modelIsResetting;
            QHash<int, QByteArray> roleNames;
			DatabaseThread * databaseThread;
			ContactsContainer contactsContainer;
			mutable CreateWorker createWorker;
			mutable ReadWorker readWorker;
			mutable UpdateWorker updateWorker;
			mutable DeleteWorker deleteWorker;
			mutable internal::WorkingCounter workingCounter;
        };

		MPtr<Members> m;
};

}
}



#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
