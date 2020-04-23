#ifndef ABSTRACTWRITER_HPP
#define ABSTRACTWRITER_HPP

#include "internal/common.hpp"
#include "TagValue.hpp"
#include "Schema.hpp"

#include <cutehmi/services/Serviceable.hpp>

#include <QObject>
#include <QQmlListProperty>

namespace cutehmi {
namespace dataacquisition {

/**
 * Abstract database writer.
 */
class CUTEHMI_DATAACQUISITION_API AbstractWriter:
	public QObject,
	public services::Serviceable
{
		Q_OBJECT

	public:
		Q_PROPERTY(QQmlListProperty<cutehmi::dataacquisition::TagValue> values READ valueList)
		Q_CLASSINFO("DefaultProperty", "values")

		Q_PROPERTY(Schema * schema READ schema WRITE setSchema NOTIFY schemaChanged)

		AbstractWriter(QObject * parent = nullptr);

		QQmlListProperty<TagValue> valueList();

		Schema * schema() const;

		void setSchema(Schema * schema);

	signals:
		void schemaChanged();

	CUTEHMI_PROTECTED_SIGNALS:
		void broke();

		void started();

		void stopped();

		void databaseConnected();

		void schemaValidated();

	protected:
		typedef QList<TagValue *> TagValueContainer;

		const TagValueContainer & values() const;

		QState * createWaitingForDatabaseConnectedSate(QState * parent, ServiceStatuses * statuses = nullptr, QState * target = nullptr);

		QState * createValidatingSchemaSate(QState * parent, ServiceStatuses * statuses = nullptr, QState * target = nullptr);

	private slots:
		void onSchemaValidated(bool result);

	private:
		static int ValueListCount(QQmlListProperty<TagValue> * property);

		static TagValue * ValueListAt(QQmlListProperty<TagValue> * property, int index);

		static void ValueListClear(QQmlListProperty<TagValue> * property);

		static void ValuesListAppend(QQmlListProperty<TagValue> * property, TagValue * value);

		struct Members
		{
			TagValueContainer values;
			QQmlListProperty<TagValue> valueList;
			Schema * schema;

			Members(AbstractWriter * p_parent):
				valueList(p_parent, & values, & AbstractWriter::ValuesListAppend, & AbstractWriter::ValueListCount, & AbstractWriter::ValueListAt, & AbstractWriter::ValueListClear),
				schema(nullptr)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // ABSTRACTWRITER_HPP
