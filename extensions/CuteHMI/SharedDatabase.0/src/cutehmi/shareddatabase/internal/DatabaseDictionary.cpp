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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
