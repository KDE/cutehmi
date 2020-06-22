#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_POSTGRESMAINTENANCE_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_POSTGRESMAINTENANCE_HPP

#include "internal/common.hpp"
#include "DataObject.hpp"

namespace cutehmi {
namespace shareddatabase {

/**
 * PostgreSQL database maintenance.
 */
class CUTEHMI_SHAREDDATABASE_API PostgresMaintenance:
	public DataObject
{
		Q_OBJECT

	public:
		PostgresMaintenance(QObject * parent = nullptr);

	public slots:
		/**
		 * Create database.
		 * @param name name of the database to be created.
		 * @param withArgs arguments passed to SQL query. PostgreSQL create database query accepts parameters after `WITH` keyword.
		 * This parameter can be used to specify them.
		 */
		void createDatabase(const QString & name, const QVariantMap & withArgs = QVariantMap());

		/**
		 * Drop database.
		 * @param name name of the database to be dropped.
		 */
		void dropDatabase(const QString & name);
};

}
}

#endif
