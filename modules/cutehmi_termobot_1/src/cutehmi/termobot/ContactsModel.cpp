#include "../../../include/cutehmi/termobot/ContactsModel.hpp"
#include <cutehmi/Worker.hpp>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>

namespace cutehmi {
namespace termobot {

ContactsModel::ContactsModel(DatabaseThread * databaseThread):
	m(new Members{false, QAbstractListModel::roleNames(), databaseThread, {}, {*databaseThread}, {*databaseThread}, {*databaseThread}, {*databaseThread}, {std::bind(& ContactsModel::busyChanged, this)}})
{
	m->roleNames[static_cast<int>(Role::DatabaseId)] = "databaseId";
    m->roleNames[static_cast<int>(Role::Nick)] = "nick";
	m->roleNames[static_cast<int>(Role::FirstName)] = "firstName";
    m->roleNames[static_cast<int>(Role::LastName)] = "lastName";
    m->roleNames[static_cast<int>(Role::Active)] = "active";
	m->roleNames[static_cast<int>(Role::EmailId)] = "emailId";
	m->roleNames[static_cast<int>(Role::Email)] = "email";
	m->roleNames[static_cast<int>(Role::PhoneId)] = "phoneId";
	m->roleNames[static_cast<int>(Role::PhoneNumber)] = "phoneNumber";

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

		for (int i = 0; i < m->contactsContainer.length(); ++i) {
			if (m->contactsContainer.at(i).databaseId == m->deleteWorker.databaseId()) {
				m->contactsContainer.removeAt(i);
				break;
			}
		}
		m->deleteWorker.setDatabaseId(0);
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
		if (role == static_cast<int>(Role::DatabaseId))
			return contact.databaseId;
		else if (role == static_cast<int>(Role::Nick))
			return contact.nick;
		else if (role == static_cast<int>(Role::FirstName))
			return contact.firstName;
		else if (role == static_cast<int>(Role::LastName))
			return contact.lastName;
		else if (role == static_cast<int>(Role::Active))
			return contact.enabled;
		else if (role == static_cast<int>(Role::PhoneId))
			return contact.phoneId;
		else if (role == static_cast<int>(Role::PhoneNumber))
			return contact.phoneNumber;
		else if (role == static_cast<int>(Role::EmailId))
			return contact.emailId;
		else if (role == static_cast<int>(Role::Email))
			return contact.email;
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

bool ContactsModel::update(const unsigned int & databaseId, const QString & newNick, const QString & newFirstName, const QString & newLastName, const unsigned int & phoneId, const QString & newPhoneNumber, const unsigned int & emailId, const QString & newEmail, const bool & newActive)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	// Find a row number which changes.
	int row = -1;
	for (int i = 0; i < m->contactsContainer.length(); ++i) {
		if (m->contactsContainer.at(i).databaseId == databaseId) {
			row = i;
			break;
		}
	}
	if (row == -1)
		return false;

	// Create new contact tuple.
	std::unique_ptr<ContactTuple> contact(new ContactTuple{databaseId, newNick, newFirstName, newLastName, phoneId, newPhoneNumber, emailId, newEmail, newActive});

	// Prepare worker to work.
	m->updateWorker.changedRow(row);
	m->updateWorker.contact(std::move(contact));

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

bool ContactsModel::remove(unsigned int databaseId)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	// Find row number with a proper nick.
	int row = -1;
	for (int i = 0; i < m->contactsContainer.length(); ++i) {
		if (m->contactsContainer.at(i).databaseId == databaseId) {
			row = i;
			break;
		}
	}
	if (row == -1)
		return false;

	beginRemoveRows(QModelIndex(), row, row);
	++m->workingCounter;
	m->deleteWorker.setDatabaseId(databaseId);
	m->deleteWorker.work();

	return true;
}

bool ContactsModel::insert(const QString & nick, const QString & firstName, const QString & lastName, const QString & phoneNumber, const QString & email, const bool & enabled)
{
	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return false;
	}

	std::unique_ptr<ContactTuple> contact(new ContactTuple{{}, nick, firstName, lastName, {}, phoneNumber, {}, email, enabled});

	// Check if nick is unique (if not then early return false).
	for (int i = 0; i < m->contactsContainer.length(); ++i) {
		if (m->contactsContainer.at(i).nick == nick) {
			return false;
		}
	}

	// Append contact to the end of the list.
	int endRow = m->contactsContainer.count();

	++m->workingCounter;
	beginInsertRows(QModelIndex(), endRow, endRow);
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

	// Insert contact with email and phone number into three tables in one statement.
	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("WITH new_contact AS ( "
				  "INSERT INTO contacts (nick, first_name, last_name, enabled) "
				  "VALUES (:nick, :first_name, :last_name, :enabled) "
				  "RETURNING id), new_phone_number AS ( "
				  "INSERT INTO phone_numbers (contact_id, phone_number) "
				  "VALUES ((SELECT id FROM new_contact), :phone_number) RETURNING *) "
				  "INSERT INTO emails (contact_id, address) "
				  "VALUES ((SELECT id FROM new_contact), :address)");
	query.bindValue(":nick", m_contact->nick);
	query.bindValue(":first_name", m_contact->firstName);
	query.bindValue(":last_name", m_contact->lastName);
	query.bindValue(":enabled", m_contact->enabled);
	query.bindValue(":phone_number", m_contact->phoneNumber);
	query.bindValue(":address", m_contact->email);
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

	QSqlQuery contactsQuery(QSqlDatabase::database(m_connectionName, false));
	contactsQuery.exec("SELECT DISTINCT ON (contacts.id) contacts.id, contacts.nick, "
					   "contacts.first_name, contacts.last_name, contacts.enabled, "
					   "phone_numbers.id AS phone_id, phone_numbers.phone_number, "
					   "emails.id AS email_id, emails.address FROM "
					   "(contacts LEFT JOIN phone_numbers ON contacts.id = phone_numbers.contact_id) "
					   "LEFT JOIN emails ON contacts.id = emails.contact_id");
	QSqlRecord record = contactsQuery.record();
	while (contactsQuery.next()) {
		m_contacts.push_back(ContactTuple{
								 contactsQuery.value(record.indexOf("id")).toUInt(),
								 contactsQuery.value(record.indexOf("nick")).toString(),
								 contactsQuery.value(record.indexOf("first_name")).toString(),
								 contactsQuery.value(record.indexOf("last_name")).toString(),
								 contactsQuery.value(record.indexOf("phone_id")).toUInt(),
								 contactsQuery.value(record.indexOf("phone_number")).toString(),
								 contactsQuery.value(record.indexOf("email_id")).toUInt(),
								 contactsQuery.value(record.indexOf("address")).toString(),
								 contactsQuery.value(record.indexOf("enabled")).toBool()
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

	QSqlDatabase connection = QSqlDatabase::database(m_connectionName, false);

	// Count how many emails has got updated contact.
	QSqlQuery emailCountQuery(connection);
	emailCountQuery.prepare("SELECT COUNT(*) FROM emails WHERE contact_id = :contact_id");
	emailCountQuery.bindValue(":contact_id", m_contact->databaseId);
	emailCountQuery.exec();
	QSqlRecord emailCountRecord = emailCountQuery.record();
	emailCountQuery.first();
	unsigned int emailsCount = emailCountQuery.value(emailCountRecord.indexOf("count")).toUInt();

	// Prepare query for updating email.
	// If the contact doesn't have any emails then create one, otherwise update one.
	QSqlQuery updateEmailQuery(connection);
	if (emailsCount == 0)
		updateEmailQuery.prepare("INSERT INTO emails VALUES (:contact_id, :address)");
	else
		updateEmailQuery.prepare("UPDATE emails SET address = :address WHERE contact_id = :contact_id AND id = :email_id");
	updateEmailQuery.bindValue(":contact_id", m_contact->databaseId);
	updateEmailQuery.bindValue(":address", m_contact->email);
	updateEmailQuery.bindValue(":email_id", m_contact->emailId);


	// Count how many phone numbers has got updated contact.
	QSqlQuery phoneCountQuery(connection);
	phoneCountQuery.prepare("SELECT COUNT(*) FROM phone_numbers WHERE contact_id = :contact_id");
	phoneCountQuery.bindValue(":contact_id", m_contact->databaseId);
	phoneCountQuery.exec();
	QSqlRecord phoneCountRecord = phoneCountQuery.record();
	phoneCountQuery.first();
	unsigned int phonesCount = phoneCountQuery.value(phoneCountRecord.indexOf("count")).toUInt();

	// Prepare query for updating phone number.
	// If the contact doesn't have any phone numbers then create one, otherwise update one.
	QSqlQuery updatePhoneQuery(connection);
	if (phonesCount == 0)
		updatePhoneQuery.prepare("INSERT INTO phone_numbers VALUES (:contact_id, :phone_number)");
	else
		updatePhoneQuery.prepare("UPDATE phone_numbers SET phone_number = :phone_number WHERE contact_id = :contact_id AND id = :phone_id");
	updatePhoneQuery.bindValue(":contact_id", m_contact->databaseId);
	updatePhoneQuery.bindValue(":phone_number", m_contact->phoneNumber);
	updatePhoneQuery.bindValue(":phone_id", m_contact->phoneId);

	// Prepare query for updating contact.
	QSqlQuery updateContactQuery(connection);
	updateContactQuery.prepare("UPDATE contacts SET nick = :new_nick, first_name = :new_first_name, last_name = :new_last_name, enabled = :new_enabled WHERE id = :id");
	updateContactQuery.bindValue(":new_nick", m_contact->nick);
	updateContactQuery.bindValue(":new_first_name", m_contact->firstName);
	updateContactQuery.bindValue(":new_last_name", m_contact->lastName);
	updateContactQuery.bindValue(":new_enabled", m_contact->enabled);
	updateContactQuery.bindValue(":id", m_contact->databaseId);

	// Execute all queries in one transaction.
	connection.transaction();
	updateContactQuery.exec();
	updateContactQuery.finish();
	updateEmailQuery.exec();
	updateEmailQuery.finish();
	updatePhoneQuery.exec();
	updatePhoneQuery.finish();
	connection.commit();

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

	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("DELETE FROM contacts WHERE id = :id");
	query.bindValue(":id", m_databaseId);
	query.exec();

	CUTEHMI_LOG_DEBUG("Delete worker finished.");
}

void ContactsModel::DeleteWorker::setDatabaseId(const unsigned int & databaseId)
{
	m_databaseId = databaseId;
}

const unsigned int & ContactsModel::DeleteWorker::databaseId() const
{
	return m_databaseId;
}

}
}

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
