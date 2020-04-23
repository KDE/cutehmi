#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TAGCACHE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TAGCACHE_HPP

#include "common.hpp"
#include "TableObject.hpp"

#include <QReadWriteLock>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE TagCache:
	public TableObject
{
	public:
		explicit TagCache(Schema * schema, QObject * parent = nullptr);

		int getId(const QString & name, QSqlDatabase & db);

	protected:
		void insert(const QString & name, QSqlDatabase & db);

		void update(QSqlDatabase & db);

	private:
		typedef QHash<QString, int> TagIdContainter;

		struct Members
		{
			Schema * schema;
			TagIdContainter tagIds;
			QReadWriteLock tagIdsLock;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
