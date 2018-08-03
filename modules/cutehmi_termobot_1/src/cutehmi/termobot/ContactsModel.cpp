#include "../../../include/cutehmi/termobot/ContactsModel.hpp"
#include <cutehmi/Worker.hpp>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>

namespace cutehmi {
namespace termobot {

ContactsModel::ContactsModel(DatabaseThread * databaseThread):
	m(new Members{false, QAbstractListModel::roleNames(), databaseThread, {}, {*databaseThread}, {*databaseThread}, {*databaseThread}, {*databaseThread}, {std::bind(& ContactsModel::busyChanged, this)}})
{
    m->roleNames[static_cast<int>(Role::Nick)] = "nick";
    m->roleNames[static_cast<int>(Role::FirstName)] = "firstName";
    m->roleNames[static_cast<int>(Role::LastName)] = "lastName";
    m->roleNames[static_cast<int>(Role::Active)] = "active";

	connect(& m->createWorker, & CreateWorker::ready, this, [this]() {
		endInsertRows();
		--m->workingCounter;
	});

	connect(& m->readWorker, & ReadWorker::ready, this, [this]() {
		if (m->contactsContainer.length() != m->readWorker.contacts().length()) {
			beginResetModel();
			m->modelIsResetting = true;
			m->contactsContainer = m->readWorker.contacts();
			endResetModel();
			m->modelIsResetting = false;
		}
		--m->workingCounter;
	});

	connect(& m->updateWorker, & UpdateWorker::ready, this, [this]() {
		m->contactsContainer.replace(m->updateWorker.changedRow(), m->updateWorker.contact());
		QModelIndex changedIndex = createIndex(m->updateWorker.changedRow(), 1);
		dataChanged(changedIndex, changedIndex);
		--m->workingCounter;
	});

	connect(& m->deleteWorker, & DeleteWorker::ready, this, [this]() {
		endRemoveRows();
		--m->workingCounter;
	});
}

ContactsModel::~ContactsModel()
{
}

bool ContactsModel::busy() const
{
	return static_cast<bool>(m->workingCounter) || !m->databaseThread->isRunning();
}

QVariant ContactsModel::data(const QModelIndex & index, int role) const
{
	if (index.isValid()) {
		ContactTuple contact = m->contactsContainer[index.row()];
		if (role == static_cast<int>(Role::Nick))
			return contact.nick;
		else if (role == static_cast<int>(Role::FirstName))
			return contact.firstName;
		else if (role == static_cast<int>(Role::LastName))
			return contact.lastName;
		else if (role == static_cast<int>(Role::Active))
			return contact.enabled;
	}
	return QVariant();
}

int ContactsModel::rowCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);

	CUTEHMI_LOG_DEBUG("entering rowCount");


	if (m->readWorker.isWorking())
		CUTEHMI_LOG_WARNING("Ignoring request, because worker has not finished its previous job yet.");
	else if (m->modelIsResetting)
		CUTEHMI_LOG_WARNING("Ignoring request, because model is being reset.");
	else if (!m->databaseThread->isRunning())
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
	else {
		++m->workingCounter;
		m->readWorker.work();
	}

	return m->contactsContainer.count();
}

bool ContactsModel::update(const QString & nick, const QString & newNick, const QString & newFirstName, const QString & newLastName, const bool & newActive)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	// Find a row number which changes.
	int row = -1;
	for (int i = 0; i < m->contactsContainer.length(); ++i) {
		if (m->contactsContainer.at(i).nick == nick) {
			row = i;
			break;
		}
	}
	if (row == -1)
		return false;

	// Create new contact tuple.
	std::unique_ptr<ContactTuple> contact(new ContactTuple{newNick, newFirstName, newLastName, newActive});

	// Prepare worker to work.
	m->updateWorker.changedRow(row);
	m->updateWorker.contact(std::move(contact));
	m->updateWorker.nick(nick);

	// Increment workingCounter by one.
	++m->workingCounter;

	// Start the worker.
	m->updateWorker.work();

	return true;
}

Qt::ItemFlags ContactsModel::flags(const QModelIndex &index) const
{
	Q_UNUSED(index);

	Qt::ItemFlags flags;
	if (m->databaseThread->isRunning()) {
		flags.setFlag(Qt::ItemIsEditable);
		flags.setFlag(Qt::ItemIsUserCheckable);
	} else
		flags.setFlag(Qt::NoItemFlags);

	return flags;
}

bool ContactsModel::remove(QString nick)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	// Find row number with a proper nick.
	int row = -1;
	for (int i = 0; i < m->contactsContainer.length(); ++i) {
		if (m->contactsContainer.at(i).nick == nick) {
			row = i;
			break;
		}
	}
	if (row == -1)
		return false;

	beginRemoveRows(QModelIndex(), row, row);
	++m->workingCounter;
	m->deleteWorker.nick(nick);
	m->deleteWorker.work();

	return true;
}

bool ContactsModel::insert(QString nick, QString firstName, QString lastName, bool enabled)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	std::unique_ptr<ContactTuple> contact(new ContactTuple{nick, firstName, lastName, enabled});

	// Check if nick is unique (if not then early return false).
	for (int i = 0; i < m->contactsContainer.length(); ++i) {
		if (m->contactsContainer.at(i).nick == nick) {
			return false;
		}
	}

	// Calculate insertion row.
	int row = 0;
	for (int i = 0; i < m->contactsContainer.length(); ++i) {
		if (m->contactsContainer.at(i).nick > nick) {
			row = i;
			break;
		}
	}


	++m->workingCounter;
	beginInsertRows(QModelIndex(), row, row);
	m->createWorker.contact(std::move(contact));
	m->createWorker.work();
	return true;
}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    return m->roleNames;
}

ContactsModel::CreateWorker::CreateWorker(DatabaseThread &databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void ContactsModel::CreateWorker::job()
{
	CUTEHMI_LOG_DEBUG("Create worker starts its own job...");

	if (m_contact == nullptr) {
		CUTEHMI_LOG_WARNING("Started create worker with empty m_contact.");
		return;
	}

	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("INSERT INTO contacts (nick, first_name, last_name, enabled) VALUES (:nick, :first_name, :last_name, :enabled)");
	query.bindValue(":nick", m_contact->nick);
	query.bindValue(":first_name", m_contact->firstName);
	query.bindValue(":last_name", m_contact->lastName);
	query.bindValue(":enabled", m_contact->enabled);
	query.exec();

	m_contact.reset(nullptr);

	CUTEHMI_LOG_DEBUG("Create worker finished.");
}

void ContactsModel::CreateWorker::contact(std::unique_ptr<ContactTuple> newContact)
{
	m_contact.reset(newContact.release());
}

ContactsModel::ReadWorker::ReadWorker(DatabaseThread & databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void ContactsModel::ReadWorker::job()
{
	CUTEHMI_LOG_DEBUG("Read worker starts its own job...");
	m_contacts.clear();

	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.exec("SELECT * FROM contacts ORDER BY nick");
	QSqlRecord record = query.record();
	while (query.next()) {
		m_contacts.push_back(ContactTuple{
								 query.value(record.indexOf("nick")).toString(),
								 query.value(record.indexOf("first_name")).toString(),
								 query.value(record.indexOf("last_name")).toString(),
								 query.value(record.indexOf("enabled")).toBool()
							 });
	}
	CUTEHMI_LOG_DEBUG("Read worker finished.");
}

const ContactsModel::ContactsContainer & ContactsModel::ReadWorker::contacts() const
{
	return m_contacts;
}

ContactsModel::UpdateWorker::UpdateWorker(DatabaseThread &databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void ContactsModel::UpdateWorker::job()
{
	CUTEHMI_LOG_DEBUG("Update worker starts its own job...");

	if (m_contact == nullptr) {
		CUTEHMI_LOG_WARNING("Started update worker with empty m_contact.");
		return;
	}

	if (m_nick.isNull()) {
		CUTEHMI_LOG_WARNING("Started update worker with null m_nick.");
		return;
	}

	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("UPDATE contacts SET nick = :new_nick, first_name = :new_first_name, last_name = :new_last_name, enabled = :new_enabled WHERE nick = :nick");
	query.bindValue(":new_nick", m_contact->nick);
	query.bindValue(":new_first_name", m_contact->firstName);
	query.bindValue(":new_last_name", m_contact->lastName);
	query.bindValue(":new_enabled", m_contact->enabled);
	query.bindValue(":nick", m_nick);
	query.exec();

	nick(QString());

	CUTEHMI_LOG_DEBUG("Update worker finished.");
}

const ContactsModel::ContactTuple & ContactsModel::UpdateWorker::contact() const
{
	return *m_contact;
}

void ContactsModel::UpdateWorker::contact(std::unique_ptr<ContactTuple> newContact)
{
	m_contact.reset(newContact.release());
}

void ContactsModel::UpdateWorker::nick(const QString &newNick)
{
	m_nick = newNick;
}

const int & ContactsModel::UpdateWorker::changedRow() const
{
	return m_changedRow;
}

void ContactsModel::UpdateWorker::changedRow(const int &newRow)
{
	m_changedRow = newRow;
}

ContactsModel::DeleteWorker::DeleteWorker(DatabaseThread & databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void ContactsModel::DeleteWorker::job()
{
	CUTEHMI_LOG_DEBUG("Delete worker starts its own job...");

	if (m_nick.isNull()) {
		CUTEHMI_LOG_WARNING("Started delete worker with null nick.");
		return;
	}

	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("DELETE FROM contacts WHERE nick = :nick");
	query.bindValue(":nick", m_nick);
	query.exec();

	nick(QString());

	CUTEHMI_LOG_DEBUG("Delete worker finished.");
}

void ContactsModel::DeleteWorker::nick(const QString &newNick)
{
	m_nick = newNick;
}

}
}

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
