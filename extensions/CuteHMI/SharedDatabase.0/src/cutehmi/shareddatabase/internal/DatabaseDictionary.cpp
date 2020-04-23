#include "DatabaseDictionary.hpp"

namespace cutehmi {
namespace shareddatabase {
namespace internal {

void DatabaseDictionary::associateThread(const QString & connectionName, QThread * thread)
{
	m->threads.insert(connectionName, thread);
	emit threadChanged(connectionName);
}

int DatabaseDictionary::dissociateThread(const QString & connectionName)
{
	int result = m->threads.remove(connectionName);
	emit threadChanged(connectionName);
	return result;
}

QThread * DatabaseDictionary::associatedThread(const QString & connectionName) const
{
	return m->threads.value(connectionName, nullptr);
}

void DatabaseDictionary::addConnected(const QString & connectionName)
{
	m->connected.insert(connectionName);
}

void DatabaseDictionary::removeConnected(const QString & connectionName)
{
	m->connected.remove(connectionName);
}

bool DatabaseDictionary::isConnected(const QString & connectionName) const
{
	return m->connected.contains(connectionName);
}

void DatabaseDictionary::addManaged(const QString & connectionName)
{
	m->managed.insert(connectionName);
}

void DatabaseDictionary::removeManaged(const QString & connectionName)
{
	m->managed.remove(connectionName);
}

bool DatabaseDictionary::isManaged(const QString & connectionName) const
{
	return m->managed.contains(connectionName);
}

DatabaseDictionary::DatabaseDictionary():
	m(new Members)
{
}

}
}
}
