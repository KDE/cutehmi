#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_EVENTCOLLECTIVE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_EVENTCOLLECTIVE_HPP

#include "common.hpp"
#include "TagCache.hpp"
#include "TableCollective.hpp"

namespace cutehmi {
namespace dataacquisition {

class TagValue;

namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE EventCollective:
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

			//<CuteHMI.DataAcquisition-1.workaround target="clang" cause="Bug-28280">
			~ColumnValues();
			//</CuteHMI.DataAcquisition-1.workaround>

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

		EventCollective();

		void insert(const TagValue & tag);

		void select(const QStringList & tags, const QDateTime & from, const QDateTime & to);

	signals:
		void selected(cutehmi::dataacquisition::internal::EventCollective::ColumnValues result, QDateTime minTime, QDateTime maxTime);

	private:
		QString selectQuery(const QString & driverName, const QString & schemaName, const QString & tableName, const QStringList & tagIdtrings, const QDateTime & from, const QDateTime & to);

		template<typename T>
		bool tableSelect(QSqlDatabase & db, ColumnValues & columnValues, const QString & schemaName, const QStringList & tags, const QDateTime & from, const QDateTime & to);

		template<typename T>
		bool tableMinTime(QSqlDatabase & db, QDateTime & minTime, const QString & schemaName);

		template<typename T>
		bool tableMaxTime(QSqlDatabase & db, QDateTime & maxTime, const QString & schemaName);

		template <typename T>
		void insertIntoTable(const TagValue & tag);
};

}
}
}

Q_DECLARE_METATYPE(cutehmi::dataacquisition::internal::EventCollective::ColumnValues)

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
