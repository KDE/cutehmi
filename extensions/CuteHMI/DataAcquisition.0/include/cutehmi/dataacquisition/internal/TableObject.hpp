#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TABLEOBJECT_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TABLEOBJECT_HPP

#include "common.hpp"
#include "../Schema.hpp"

#include <cutehmi/shareddatabase/DataObject.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE TableObject:
	public shareddatabase::DataObject

{
		Q_OBJECT

	public:
		Q_PROPERTY(QString connectionName READ connectionName NOTIFY connectionNameChanged)	// Overriden.

		Q_PROPERTY(Schema * schema READ schema WRITE setSchema NOTIFY schemaChanged)

		explicit TableObject(Schema * schema = nullptr, QObject * parent = nullptr);

		Schema * schema() const;

		void setSchema(Schema * schema);

	signals:
		void schemaChanged();

	protected:
		QString getSchemaName() const;

	private:
		struct Members
		{
			Schema * schema;
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
