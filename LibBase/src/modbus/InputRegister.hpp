#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_INPUTREGISTER_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_INPUTREGISTER_HPP

#include "../platform.hpp"

#include <QObject>

namespace modbus {

/**
 * Modbus input register.
 *
 * @note to make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 *
 * @internal QML type is registered in ModbusClientPlugin class.
 */
class CUTEHMI_API InputRegister:
	public QObject
{
	Q_OBJECT
	Q_PROPERTY(qint16 int16 READ int16 NOTIFY valueChanged)

	public:
		explicit InputRegister(qint16 value = 0, QObject * parent = 0);

		qint16 int16() const;

		void setInt16(qint16 value);

	signals:
		void valueChanged();

	private:
		qint16 m_value;
};

}

#endif
