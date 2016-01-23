#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_HOLDINGREGISTER_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_HOLDINGREGISTER_HPP

#include "../platform.hpp"

#include <QObject>
#include <QMutex>
#include <QReadWriteLock>
#include <QVariant>

namespace modbus {

/**
 * Modbus holding register. According to Modbus specification register holds 16 bit data.
 *
 * @note to make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 *
 * @todo remove int16 property and planned uint16, bcd.
 */
class CUTEHMI_MODBUS_API HoldingRegister:
	public QObject
{
	Q_OBJECT
	Q_PROPERTY(qint16 int16 READ int16 WRITE setInt16 NOTIFY valueChanged)
//	Q_PROPERTY(quint16 uint16 READ uint16 WRITE setUint16 NOTIFY valueChanged STORED false)
//	Q_PROPERTY(qint16 bcd READ bcd NOTIFY valueChanged STORED false)

	public:
		enum encoding_t {
			INT16
		};
		Q_ENUM(encoding_t)

		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit HoldingRegister(uint16_t int16 = 0, QObject * parent = 0);

		qint16 int16() const;

		void setInt16(qint16 int16);

		Q_INVOKABLE QVariant value(encoding_t encoding = INT16) const;

		Q_INVOKABLE uint16_t requestedValue() const;

	public slots:
		void requestValue(QVariant value, encoding_t encoding = INT16);

		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(uint16_t value);

	signals:
		void valueChanged();	///< @todo remove.

		void valueRequested();

		void valueUpdated();

	private:
		uint16_t m_value;
		mutable QReadWriteLock m_valueLock;
		uint16_t m_reqValue;
		mutable QMutex m_reqValueMutex;
};

}

#endif
