#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_RECENCYMODEL_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_RECENCYMODEL_HPP

#include "internal/common.hpp"

#include "AbstractListModel.hpp"
#include "internal/RecencyCollective.hpp"
#include "internal/ModelMixin.hpp"

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API RecencyModel:
	public AbstractListModel,
	private internal::ModelMixin<RecencyModel>
{
		Q_OBJECT

		typedef AbstractListModel Parent;

		friend class internal::ModelMixin<RecencyModel>;

	public:
		enum Role {
			TAG_ROLE = Qt::UserRole,
			VALUE_ROLE,
			TIME_ROLE
		};

		Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged)

		RecencyModel(QObject * parent = nullptr);

		QStringList tags() const;

		void setTags(const QStringList & tags);

		bool busy() const override;

		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		QHash<int, QByteArray> roleNames() const override;

		int rowCount(const QModelIndex & parent = QModelIndex()) const override;

	signals:
		void tagsChanged();

	public slots:
		void requestUpdate() override;

	protected slots:
		void confirmUpdateFinished() override;

	private slots:
		void onSchemaChanged();

		void onSelected(internal::RecencyCollective::ColumnValues columnValues);

	private:
		struct Members {
			internal::RecencyCollective::ColumnValues columnValues;
			internal::RecencyCollective dbCollective;
			QStringList tags;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
