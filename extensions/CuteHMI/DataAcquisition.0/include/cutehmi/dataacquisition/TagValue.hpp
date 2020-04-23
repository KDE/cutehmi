#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_TAGVALUE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_TAGVALUE_HPP

#include "internal/common.hpp"

#include <QObject>

namespace cutehmi {
namespace dataacquisition {

/**
 * Tag value. This class associates tag with a value. Tag acts as a universal SCADA variable identifier. Value is typically binded
 * to some data source.
 */
class CUTEHMI_DATAACQUISITION_API TagValue:
	public QObject
{
		Q_OBJECT

	public:
		/**
		  Tag name.
		  */
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

		/**
		  Value. Type of QML value must be either @p int, @p real or @p bool (or @p int, @p double and @p bool in C++).
		  */
		Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)

		/**
		 * Constructor.
		 * @param parent parent object.
		 */
		TagValue(QObject * parent = nullptr);

		/**
		 * Get tag name.
		 * @return tag name.
		 */
		QString name() const;

		/**
		 * Set tag name.
		 * @param name tag name.
		 */
		void setName(const QString & name);

		/**
		 * Get value.
		 * @return value.
		 */
		QVariant value() const;

		/**
		 * Set value.
		 * @param value value.
		 */
		void setValue(const QVariant & value);

		/**
		 * Get type name of actually stored value. This function may be useful for debugging purposes.
		 * @return C++ type name of actually stored value.
		 */
		Q_INVOKABLE QString typeName() const;

	signals:
		void nameChanged();

		void valueChanged();

	private:
		struct Members {
			QString name;
			QVariant value;
		};

		MPtr<Members> m;
};

}
}

#endif
