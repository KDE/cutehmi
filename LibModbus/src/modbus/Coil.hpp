#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_COIL_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_COIL_HPP

#include "../platform.hpp"

#include <QObject>
#include <QMutex>
#include <QReadWriteLock>
#include <QAtomicInt>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API Coil:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit Coil(bool value = false, QObject * parent = 0);

		Q_INVOKABLE bool value() const;

		Q_INVOKABLE bool requestedValue() const;

		Q_INVOKABLE void rest();

		Q_INVOKABLE void awake();

		Q_INVOKABLE bool wakeful() const;

	public slots:
		void requestValue(bool value);

		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(bool value);

	signals:
		void valueRequested();

		void valueUpdated();

		/**
		 * Value written. This signal is emitted when requested value has been written to the client device.
		 */
		void valueWritten();

	private:
		bool m_value;
		mutable QReadWriteLock m_valueLock;
		bool m_reqValue;
		mutable QMutex m_reqValueMutex;
		QAtomicInt m_awaken;
};

}
}

#endif
