#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_INPUTREGISTER_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_INPUTREGISTER_HPP

#include "../platform.hpp"

#include <QObject>
#include <QMutex>

namespace cutehmi {
namespace modbus {

/**
 * Modbus input register.
 *
 * @note to make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 */
class CUTEHMI_MODBUS_API InputRegister:
	public QObject
{
	Q_OBJECT
	Q_PROPERTY(qint16 int16 READ int16 NOTIFY valueChanged)

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit InputRegister(uint16_t value = 0, QObject * parent = 0);

		qint16 int16() const;

		void setInt16(qint16 value);

	public slots:
		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(uint16_t value);

	signals:
		void valueChanged();

		void valueUpdated();

	private:
		int m_address; ///< @note @p int type is enforced by Qt, which uses it for sizes and indices. This limits addressing to std::numeric_limits<int>::max().
		uint16_t m_value;
		QMutex m_valueMutex;
		uint16_t m_reqValue;
};

}
}

#endif
