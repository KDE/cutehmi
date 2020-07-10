#ifndef HISTORYMODEL_HPP
#define HISTORYMODEL_HPP

#include "internal/common.hpp"

#include "AbstractListModel.hpp"
#include "internal/HistoryCollective.hpp"
#include "internal/ModelMixin.hpp"

#include <QDateTime>

namespace cutehmi {
namespace dataacquisition {

class CUTEHMI_DATAACQUISITION_API HistoryModel:
	public AbstractListModel,
	private internal::ModelMixin<HistoryModel>
{
		Q_OBJECT

		typedef AbstractListModel Parent;

		friend class internal::ModelMixin<HistoryModel>;

	public:
		enum Role {
			TAG_ROLE = Qt::UserRole,
			OPEN_ROLE,
			CLOSE_ROLE,
			MIN_ROLE,
			MAX_ROLE,
			OPEN_TIME_ROLE,
			CLOSE_TIME_ROLE,
			COUNT_ROLE
		};

		Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged)

		Q_PROPERTY(QDateTime begin READ begin NOTIFY beginChanged)

		Q_PROPERTY(QDateTime end READ end NOTIFY endChanged)

		Q_PROPERTY(QDateTime from READ from WRITE setFrom NOTIFY fromChanged)

		Q_PROPERTY(QDateTime to READ to WRITE setTo NOTIFY toChanged)

		HistoryModel(QObject * parent = nullptr);

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

		void onSelected(internal::HistoryCollective::ColumnValues columnValues, QDateTime minOpenTime, QDateTime maxCloseTime);

	private:
		struct Members {
			internal::HistoryCollective::ColumnValues columnValues;
			internal::HistoryCollective dbCollective;
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

#endif // HISTORYMODEL_HPP
