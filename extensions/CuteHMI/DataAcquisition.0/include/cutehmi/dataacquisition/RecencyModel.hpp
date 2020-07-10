#ifndef RECENCYMODEL_HPP
#define RECENCYMODEL_HPP

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

#endif // RECENCYMODEL_HPP
