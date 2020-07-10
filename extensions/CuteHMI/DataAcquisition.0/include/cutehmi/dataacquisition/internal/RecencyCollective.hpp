#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_RECENCYCOLLECTIVE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_RECENCYCOLLECTIVE_HPP

#include "common.hpp"
#include "TableCollective.hpp"

#include <QHash>
#include <QList>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE RecencyCollective:
	public TableCollective
{
		Q_OBJECT

	public:
		static const char * TABLE_STEM;

		struct ColumnValues
		{
			QStringList tagName;
			QVariantList value;
			QVariantList time;

			int length() const;

			bool isEqual(int i, const ColumnValues & other);

			void replace(int i, const ColumnValues & other);

			void insert(int i, const ColumnValues & other);

			void eraseFrom(int i);

			void append(const ColumnValues & other, int i);
		};

		struct Tuple
		{
			QVariant value;
			QDateTime time;
		};

		typedef QHash<QString, Tuple> TuplesContainer;

		RecencyCollective();

		void update(const TuplesContainer & tuples);

		void select(const QStringList & tags);

	signals:
		void selected(cutehmi::dataacquisition::internal::RecencyCollective::ColumnValues result);

	protected:
		static void ToColumnValues(ColumnValues & intValues, ColumnValues & boolValues, ColumnValues & realValues, const TuplesContainer & tuples);

	private:
		QString updateQuery(const QString & driverName, const QString & schemaName, const QString & tableName);

		QString selectQuery(const QString & driverName, const QString & schemaName, const QString & tableName, const QStringList & tagIdtrings);

		template<typename T>
		void tableUpdate(QSqlDatabase & db, const QString & schemaName, const ColumnValues & columnValues);

		template<typename T>
		bool tableSelect(QSqlDatabase & db, ColumnValues & columnValues, const QString & schemaName, const QStringList & tags);
};

}
}
}

Q_DECLARE_METATYPE(cutehmi::dataacquisition::internal::RecencyCollective::ColumnValues)

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
