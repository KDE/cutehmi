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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
