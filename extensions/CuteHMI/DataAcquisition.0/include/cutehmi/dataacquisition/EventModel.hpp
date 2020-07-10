#ifndef EVENTMODEL_HPP
#define EVENTMODEL_HPP

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

#endif // EVENTMODEL_HPP
