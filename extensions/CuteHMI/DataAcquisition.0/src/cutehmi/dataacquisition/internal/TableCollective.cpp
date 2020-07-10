#include <cutehmi/dataacquisition/internal/TableCollective.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

TableCollective::TableCollective():
	m(new Members)
{
	connect(this, & TableObject::schemaChanged, this, & TableCollective::onSchemaChanged);
}

TagCache * TableCollective::tagCache() const
{
	CUTEHMI_ASSERT(m->tagCache.get(), "object must not be nullptr");

	return m->tagCache.get();
}

void TableCollective::onSchemaChanged()
{
	m->tagCache.reset(new TagCache(schema()));
	connect(m->tagCache.get(), & shareddatabase::DataObject::errored, this, & TableCollective::errored);
}

}
}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
