#ifndef TABLEOBJECT_HPP
#define TABLEOBJECT_HPP

#include "common.hpp"
#include "../DataObject.hpp"
#include "../Schema.hpp"


namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE TableObject:
	public DataObject

{
		Q_OBJECT

	public:
		Q_PROPERTY(QString connectionName READ connectionName NOTIFY connectionNameChanged)	// Overriden.

		Q_PROPERTY(Schema * schema READ schema WRITE setSchema NOTIFY schemaChanged)

		explicit TableObject(Schema * schema, QObject * parent = nullptr);

		Schema * schema() const;

		void setSchema(Schema * schema);

	signals:
		void schemaChanged();

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

#endif // TABLEOBJECT_HPP
