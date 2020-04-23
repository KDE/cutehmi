#ifndef SCHEMA_HPP
#define SCHEMA_HPP

#include "internal/common.hpp"
#include "DataObject.hpp"

namespace cutehmi {
namespace dataacquisition {

/**
 * Database schema.
 */
class CUTEHMI_DATAACQUISITION_API Schema:
	public DataObject
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
