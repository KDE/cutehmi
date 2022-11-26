#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_1_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_HISTORYCOLLECTIVE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_1_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_HISTORYCOLLECTIVE_HPP

#include "common.hpp"
#include "TagCache.hpp"
#include "TableCollective.hpp"

#include <QDateTime>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE HistoryCollective:
	public TableCollective
{
		Q_OBJECT

	public:
		static const char * TABLE_STEM;

		struct ColumnValues
		{
			QStringList tagName;
			QVariantList open;
			QVariantList close;
			QVariantList min;
			QVariantList max;
			QVariantList openTime;
			QVariantList closeTime;
			QVariantList count;

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
			QVariant open;
			QVariant close;
			QVariant min;
			QVariant max;
			QDateTime openTime;
			QDateTime closeTime;
			int count = 0;
		};

		typedef QHash<QString, Tuple> TuplesContainer;

		HistoryCollective();

		void insert(const TuplesContainer & tuples);

		void select(const QStringList & tags, const QDateTime & from, const QDateTime & to);

	signals:
		void selected(cutehmi::dataacquisition::internal::HistoryCollective::ColumnValues result, QDateTime minOpenTime, QDateTime maxCloseTime);

	private:
		static QVariant::Type TupleVariantType(const Tuple & tuple);

		static void ToColumnValues(ColumnValues & intValues, ColumnValues & boolValues, ColumnValues & realValues, const TuplesContainer & tuples);

		QString insertQuery(const QString & driverName, const QString & schemaName, const QString & tableName);

		QString selectQuery(const QString & driverName, const QString & schemaName, const QString & tableName, const QStringList & tagIdtrings, const QDateTime & from, const QDateTime & to);

		template<typename T>
		void tableInsert(QSqlDatabase & db, const QString & schemaName, const ColumnValues & columnValues);

		template<typename T>
		bool tableSelect(QSqlDatabase & db, ColumnValues & columnValues, const QString & schemaName, const QStringList & tags, const QDateTime & from, const QDateTime & to);

		template<typename T>
		bool tableMinOpenTime(QSqlDatabase & db, QDateTime & minOpenTime, const QString & schemaName);

		template<typename T>
		bool tableMaxCloseTime(QSqlDatabase & db, QDateTime & maxCloseTime, const QString & schemaName);
};

}
}
}

Q_DECLARE_METATYPE(cutehmi::dataacquisition::internal::HistoryCollective::ColumnValues)

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
