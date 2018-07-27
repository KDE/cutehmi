#include "../../../include/cutehmi/termobot/ContactsModel.hpp"
#include <cutehmi/Worker.hpp>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>

namespace cutehmi {
namespace termobot {

ContactsModel::ContactsModel(DatabaseThread * databaseThread):
	m(new Members{QAbstractListModel::roleNames(), databaseThread, {}, {*databaseThread}, {std::bind(& ContactsModel::busyChanged, this)}})
{
    m->roleNames[static_cast<int>(Role::Nick)] = "nick";
    m->roleNames[static_cast<int>(Role::FirstName)] = "firstName";
    m->roleNames[static_cast<int>(Role::LastName)] = "lastName";
    m->roleNames[static_cast<int>(Role::Active)] = "active";

	connect(& m->readWorker, & ReadWorker::ready, this, [this]() {
		if (m->contactsContainer.length() != m->readWorker.contacts().length()) {
			beginResetModel();
			m->contactsContainer = m->readWorker.contacts();
			endResetModel();
		}
		--m->workingCounter;
	});
}

ContactsModel::~ContactsModel()
{
}

bool ContactsModel::busy() const
{
	return static_cast<bool>(m->workingCounter);
}

// TODO: implement error handling
// TODO: implement busy indicator
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

// TODO: implement error handling
// TODO: implement busy indicator
int ContactsModel::rowCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);

	if (!m->databaseThread->isRunning()) {
		CUTEHMI_LOG_WARNING("Ignoring request, because database thread is not running.");
		return m->contactsContainer.count();
	}

	if (!m->readWorker.isWorking()) {
		--m->workingCounter;
		m->readWorker.work();
	} else
		CUTEHMI_LOG_WARNING("Ignoring request, because worker has not finished its previous job yet.");

	return m->contactsContainer.count();
}

bool ContactsModel::removeRows(int row, int count, const QModelIndex & parent)
{
	beginRemoveRows(parent, row, row + count - 1);

	CUTEHMI_LOG_DEBUG("REMOVING ROWS");
//	if (m->databaseThread->isRunning())	 {
//		Worker dbWorker([this]() {
//			QSqlQuery query(QSqlDatabase::database(m->databaseThread->dbData()->connectionName, false));
//			query.exec("")
//		});
//	}
	endRemoveRows();
	return true;
}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    return m->roleNames;
}

ContactsModel::ReadWorker::ReadWorker(DatabaseThread & databaseThread):
	Worker::Worker(databaseThread),
	m_connectionName(databaseThread.dbData()->connectionName)
{
}

void ContactsModel::ReadWorker::job()
{
	CUTEHMI_LOG_DEBUG("ReadWorker starts its own job...");
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
	CUTEHMI_LOG_DEBUG("ReadWorker finished.");
}

const ContactsModel::ContactsContainer & ContactsModel::ReadWorker::contacts() const
{
	return m_contacts;
}

ContactsModel::WorkingCounter::WorkingCounter(std::function<void ()> busyChanged):
	m_busyChanged(busyChanged),
	m_counter(0)
{
}


ContactsModel::WorkingCounter & ContactsModel::WorkingCounter::operator ++()
{
	m_counter++;
	if (m_counter == 1)
		emit m_busyChanged();

	return *this;
}

ContactsModel::WorkingCounter & ContactsModel::WorkingCounter::operator --()
{
	m_counter--;
	if (m_counter == 0)
		emit m_busyChanged();

	return *this;
}

ContactsModel::WorkingCounter::operator bool() const
{
	return static_cast<bool>(m_counter);
}

}
}
