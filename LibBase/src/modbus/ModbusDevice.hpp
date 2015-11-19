#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_MODBUSDEVICE_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_MODBUSDEVICE_HPP

#include "InputRegister.hpp"

#include <QObject>
#include <QQmlListProperty>
#include <QHash>

namespace modbus {

/**
 * @todo delete.
 */
class CUTEHMI_API ModbusDevice:
		public QObject
{		
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<InputRegister> ir READ ir NOTIFY irChanged)
//	Q_PROPERTY(QQmlListProperty<ModbusHoldingRegister> r READ r NOTIFY rChanged)
//	Q_PROPERTY(QQmlListProperty<ModbusDiscreteInput> ib READ ib NOTIFY ibChanged)
//	Q_PROPERTY(QQmlListProperty<ModbusCoil> b READ b NOTIFY bChanged)

	public:
		static InputRegister * irAt(QQmlListProperty<InputRegister> * ir, int index);

		static int irCount(QQmlListProperty<InputRegister> * ir);

		ModbusDevice(QObject * parent = 0);

		virtual ~ModbusDevice() override = default;

		const QQmlListProperty<InputRegister> & ir() const;

	signals:
		void irChanged();

	private:
		// Holds (address, register) pairs. Note: Qt uses int type for sizes and indices.
		typedef QHash<int, InputRegister *> IrDataContainer;

		IrDataContainer m_irData;
		QQmlListProperty<InputRegister> m_ir;
};

}

#endif
