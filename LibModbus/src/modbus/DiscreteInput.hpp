#ifndef DISCRETEINPUT_H
#define DISCRETEINPUT_H

#include "../platform.hpp"

#include <QObject>
#include <QReadWriteLock>
#include <QAtomicInt>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API DiscreteInput:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit DiscreteInput(bool value = false, QObject * parent = 0);

		Q_INVOKABLE bool value() const;

		Q_INVOKABLE void rest();

		Q_INVOKABLE void awake();

		Q_INVOKABLE bool wakeful() const;

	public slots:
		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(bool value);

	signals:
		void valueUpdated();

	private:
		bool m_value;
		mutable QReadWriteLock m_valueLock;
		QAtomicInt m_awaken;
};

}
}

#endif // DISCRETEINPUT_H
