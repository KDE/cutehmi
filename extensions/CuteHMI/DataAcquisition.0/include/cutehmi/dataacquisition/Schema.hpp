#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_SCHEMA_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_SCHEMA_HPP

#include "internal/common.hpp"

#include <cutehmi/shareddatabase/DataObject.hpp>

namespace cutehmi {
namespace dataacquisition {

/**
 * Database schema.
 */
class CUTEHMI_DATAACQUISITION_API Schema:
	public shareddatabase::DataObject
{
		Q_OBJECT

	public:
		/**
		  Schema name.
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
		void create();

		void drop();

		/**
		 * Validate schema. Validation is performed asynchronously. Validation status can be determined by connecting to validated()
		 * signal and examining its @a result parameter.
		 */
		void validate();

	signals:
		void nameChanged();

		void userChanged();

		void validated(bool result);

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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
