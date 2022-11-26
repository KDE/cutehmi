#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_1_INCLUDE_CUTEHMI_DATAACQUISITION_SCHEMA_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_1_INCLUDE_CUTEHMI_DATAACQUISITION_SCHEMA_HPP

#include "internal/common.hpp"

#include <cutehmi/shareddatabase/DataObject.hpp>

#include <QQmlEngine>

namespace cutehmi {
namespace dataacquisition {

/**
 * Database schema.
 */
class CUTEHMI_DATAACQUISITION_API Schema:
	public cutehmi::shareddatabase::DataObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(Schema)

	public:
		static const char * INITIAL_NAME;	///< Schema name initial value ("cutehmi_dataacquisition").

		/**
		  Schema name.

		  Initial value is defined by INITIAL_NAME constant.

		  @warning DBMS may require specific schema name format. It is recommended that schema name is not empty, it starts with
		  lowercase letter or underscore and contains only lowercase letters, digits or underscore characters. Prefix "pg_" is
		  reserved by PostgreSQL for system schemas. Current implementation won't sanitize or mitigate errors, which result from
		  using unsupported schema name.
		  */
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

		/**
		  Schema user. Database defaults are used if the name is empty.
		  */
		Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)

		explicit Schema(QObject * parent = nullptr);

		QString name() const;

		void setName(const QString & name);

		QString user() const;

		void setUser(const QString & user);

	public slots:
		/**
		 * Create schema. Creation is performed asynchronously. Status of the operation can be determined by connecting to created()
		 * signal and examining its @a success parameter value.
		 */
		void create();

		/**
		 * Drop schema. Drop is performed asynchronously. Status of the operation can be determined by connecting to dropped()
		 * signal and examining its @a success parameter value.
		 */
		void drop();

		/**
		 * Validate schema. Validation is performed asynchronously. Validation status can be determined by connecting to validated()
		 * signal and examining its @a positive parameter value.
		 */
		void validate();

	signals:
		void nameChanged();

		void userChanged();

		void created(bool success);

		void dropped(bool success);

		void validated(bool positive);

	private:
		static constexpr const char * SQL_SCRIPTS_SUBDIR = "sql";
		static constexpr const char * POSTGRESQL_SCRIPTS_SUBDIR = "postgres";
		static constexpr const char * SQLITE_SCRIPTS_SUBDIR = "sqlite";

		bool validatePostgresTable(const QString & tableName, QSqlQuery & query);

		bool validateSqliteTable(const QString & tableName, QSqlQuery & query);

		QString readScript(const QString & dbms, const QString & scriptName) const;

		struct Members
		{
			QString name;
			QString user;
		};

		MPtr<Members> m;
};

}
}

#endif

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
