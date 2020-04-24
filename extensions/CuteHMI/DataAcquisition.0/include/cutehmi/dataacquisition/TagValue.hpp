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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
