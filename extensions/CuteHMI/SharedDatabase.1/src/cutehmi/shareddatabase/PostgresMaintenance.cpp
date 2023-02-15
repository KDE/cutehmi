#include "PostgresMaintenance.hpp"
#include "Exception.hpp"

namespace cutehmi {
namespace shareddatabase {

PostgresMaintenance::PostgresMaintenance(QObject * parent):
	DataObject(parent)
{
}

void PostgresMaintenance::createDatabase(const QString & name, const QVariantMap & withArgs)
{
	worker([this, name, withArgs](QSqlDatabase & db) {
		bool warning = false;
		bool error = false;

		if (db.driverName() == "QPSQL") {
			QSqlQuery query(db);
			try {
				CUTEHMI_DEBUG("Creating database...");

				QString createArgs = name;
				if (!withArgs.isEmpty()) {
					createArgs.append(" WITH");
					for (auto withIt = withArgs.begin(); withIt != withArgs.end(); ++withIt)
						createArgs.append(" ").append(withIt.key()).append(" = ").append(withIt.value().toString());
				}
				const char * createSQL = R"SQL(
CREATE DATABASE %1;
				)SQL";
				QString queryString = QString(createSQL).arg(createArgs);

				CUTEHMI_DEBUG("SQL query:\n```\n" << queryString + "\n```");
				if (!query.exec(queryString))
					error = true;

				pushError(query.lastError(), query.lastQuery());

				query.finish();
			} catch (const Exception & e) {
				CUTEHMI_CRITICAL(e.what());
				error = true;
			}
		} else {
			emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
			error = true;
		}

		if (error)
			Notification::Critical(tr("Failed to create '%1' database.").arg(name));
		else if (warning)
			Notification::Warning(tr("Created '%1' database although the operation wasn't clean.").arg(name));
		else
			Notification::Info(tr("Created '%1' database.").arg(name));
	})->work();
}

void PostgresMaintenance::dropDatabase(const QString & name)
{
	worker([this, name](QSqlDatabase & db) {
		bool warning = false;
		bool error = false;

		if (db.driverName() == "QPSQL") {
			QSqlQuery query(db);
			try {
				CUTEHMI_DEBUG("Dropping database...");

				const char * dropSQL = R"SQL(
DROP DATABASE %1;
				)SQL";
				QString queryString = QString(dropSQL).arg(name);

				CUTEHMI_DEBUG("SQL query:\n```\n" << queryString + "\n```");
				if (!query.exec(queryString))
					error = true;

				pushError(query.lastError(), query.lastQuery());

				query.finish();
			} catch (const Exception & e) {
				CUTEHMI_CRITICAL(e.what());
				error = true;
			}
		} else {
			emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
			error = true;
		}

		if (error)
			Notification::Critical(tr("Failed to drop '%1' database.").arg(name));
		else if (warning)
			Notification::Warning(tr("Dropped '%1' database although the operation wasn't clean.").arg(name));
		else
			Notification::Info(tr("Dropped '%1' database.").arg(name));
	})->work();
}

}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
