#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_HOLDINGREGISTER_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_HOLDINGREGISTER_HPP

#include "../platform.hpp"

#include <QObject>

namespace modbus {

/**
 * Modbus holding register. According to Modbus specification register holds 16 bit data.
 *
 * @note to make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 *
 * @internal QML type is registered in ModbusClientPlugin class.
 */
class CUTEHMI_API HoldingRegister:
		public QObject
{
	Q_OBJECT
	Q_PROPERTY(qint16 int16 READ int16 WRITE setInt16 NOTIFY valueChanged)
//	Q_PROPERTY(quint16 uint16 READ uint16 WRITE setUint16 NOTIFY valueChanged STORED false)
//	Q_PROPERTY(qint16 bcd READ bcd NOTIFY valueChanged STORED false)

	public:
		explicit HoldingRegister(qint16 int16 = 0, QObject * parent = 0);

		qint16 int16() const;

		void setInt16(qint16 int16);

	signals:
		void valueChanged();

	private:
		qint16 m_value;
};

}

#endif
