#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICELISTMODEL_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICELISTMODEL_HPP

#include "internal/common.hpp"
#include "Service.hpp"

#include <QAbstractListModel>

namespace cutehmi {
namespace services {

/**
 * %Notification list model.
 */
class CUTEHMI_SERVICES_API ServiceListModel:
	public QAbstractListModel
{
		Q_OBJECT
		typedef QAbstractListModel Parent;

	public:
		enum Role {
			NAME_ROLE = Qt::UserRole,
			STATUS_ROLE
		};

		ServiceListModel(QObject * parent = nullptr);

		~ServiceListModel() override;

		int rowCount(const QModelIndex & parent = QModelIndex()) const override;

		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		QHash<int, QByteArray> roleNames() const override;

		Q_INVOKABLE Service * at(int row);

		const Service * at(int row) const;

		void append(Service * service);

		void remove(Service * service);

		void clear();

	private:
		typedef QList<Service *> ServicesContainer;

		struct Members
		{
			ServicesContainer services;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
