#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TABLECOLLECTIVE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TABLECOLLECTIVE_HPP

#include "common.hpp"
#include "../Schema.hpp"

#include <QObject>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE TableCollective:
	public QObject
{
		Q_OBJECT

	public:
		TableCollective();

		Schema * schema() const;

		void setSchema(Schema * schema);

	public slots:
		void confirmWorkersFinished();

	signals:
		void workersFinished();

		void errored(cutehmi::InplaceError error);

	protected:
		virtual void updateSchema(Schema * schema) = 0;

		void accountInsertBusy(bool busy);

	private:
		struct Members
		{
			Schema * schema = nullptr;
			int insertsBusy = 0;
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
