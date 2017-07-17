#ifndef CUTEHMI_MODBUSLIB_INCLUDE_MODBUS_ABSTRACTDEVICE_HPP
#define CUTEHMI_MODBUSLIB_INCLUDE_MODBUS_ABSTRACTDEVICE_HPP

#include "internal/common.hpp"
#include "InputRegister.hpp"
#include "HoldingRegister.hpp"
#include "DiscreteInput.hpp"
#include "Coil.hpp"

#include <QObject>
#include <QQmlListProperty>

namespace cutehmi {
namespace modbus {

/**
 * Abstract Modbus device.
 */
class CUTEHMI_MODBUS_API AbstractDevice:
	public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::InputRegister> ir READ ir)
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::HoldingRegister> r READ r)
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::DiscreteInput> ib READ ib)
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::Coil> b READ b)

	//remember to delete container elements!!!
	//32 bit registers/16 bit addressing	(alternatively idr/dr (double register, then could be qr - quad for 64 bit)
	//	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::InputRegister> irr READ irr NOTIFY irChanged)
	//	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::HoldingRegister> rr READ rr NOTIFY rChanged)

	public:
		virtual const QQmlListProperty<InputRegister> & ir() = 0;

		virtual const QQmlListProperty<HoldingRegister> & r() = 0;

		virtual const QQmlListProperty<DiscreteInput> & ib() = 0;

		virtual const QQmlListProperty<Coil> & b() = 0;

		virtual InputRegister * irAt(int index) = 0;

		virtual HoldingRegister * rAt(int index) = 0;

		virtual DiscreteInput * ibAt(int index) = 0;

		virtual Coil * bAt(int index) = 0;

	protected:
		AbstractDevice(QObject * parent = 0);

		~AbstractDevice() override;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
