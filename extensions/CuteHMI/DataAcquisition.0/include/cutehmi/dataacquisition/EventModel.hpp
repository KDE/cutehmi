#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_EVENTMODEL_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_EVENTMODEL_HPP

#include "internal/common.hpp"

#include "AbstractListModel.hpp"
#include "internal/EventCollective.hpp"
#include "internal/ModelMixin.hpp"

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API EventModel:
	public AbstractListModel,
	private internal::ModelMixin<EventModel>
{
		Q_OBJECT

		typedef AbstractListModel Parent;

		friend class internal::ModelMixin<EventModel>;

	public:
		enum Role {
			TAG_ROLE = Qt::UserRole,
			VALUE_ROLE,
			TIME_ROLE,
		};

		Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged)

		Q_PROPERTY(QDateTime begin READ begin NOTIFY beginChanged)

		Q_PROPERTY(QDateTime end READ end NOTIFY endChanged)

		Q_PROPERTY(QDateTime from READ from WRITE setFrom NOTIFY fromChanged)

		Q_PROPERTY(QDateTime to READ to WRITE setTo NOTIFY toChanged)

		EventModel(QObject * parent = nullptr);

		QStringList tags() const;

		void setTags(const QStringList & tags);

		QDateTime begin() const;

		QDateTime end() const;

		QDateTime from() const;

		void setFrom(const QDateTime & from);

		QDateTime to() const;

		void setTo(const QDateTime & to);

		bool busy() const override;

		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		QHash<int, QByteArray> roleNames() const override;

		int rowCount(const QModelIndex & parent = QModelIndex()) const override;

	signals:
		void tagsChanged();

		void beginChanged();

		void endChanged();

		void fromChanged();

		void toChanged();

	public slots:
		void requestUpdate() override;

	protected slots:
		void confirmUpdateFinished() override;

	protected:
		void setBegin(const QDateTime & begin);

		void setEnd(const QDateTime & end);

	private slots:
		void onSchemaChanged();

		void onSelected(internal::EventCollective::ColumnValues columnValues, QDateTime minTime, QDateTime maxTime);

	private:
		struct Members {
			internal::EventCollective::ColumnValues columnValues;
			internal::EventCollective dbCollective;
			QStringList tags;
			QDateTime begin;
			QDateTime end;
			QDateTime from;
			QDateTime to;
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
