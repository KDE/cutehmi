#ifndef H_QML_CUTEHMI_MODBUS_SRC_CUTEHMI_MODBUS_QML_INPUTREGISTERCONTROLLER_HPP
#define H_QML_CUTEHMI_MODBUS_SRC_CUTEHMI_MODBUS_QML_INPUTREGISTERCONTROLLER_HPP

#include <cutehmi/modbus/AbstractDevice.hpp>

#include <QObject>

namespace cutehmi {
namespace modbus {
namespace qml {

class InputRegisterController:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(AbstractDevice * device READ device WRITE setDevice NOTIFY deviceChanged)
		Q_PROPERTY(int address READ address WRITE setAddress NOTIFY addressChanged)
		Q_PROPERTY(qreal value READ value NOTIFY valueChanged)
		Q_PROPERTY(qreal valueScale READ valueScale WRITE setValueScale NOTIFY valueScaleChanged)
		Q_PROPERTY(InputRegister::Encoding encoding READ encoding WRITE setEncoding NOTIFY encodingChanged)
		Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

		InputRegisterController(QObject * parent = 0);

		~InputRegisterController() override;

	public:
		AbstractDevice * device() const;

		void setDevice(AbstractDevice * device);

		int address() const;

		void setAddress(int address);

		qreal value() const;

		qreal valueScale() const;

		void setValueScale(qreal valueScale);

		InputRegister::Encoding encoding() const;

		void setEncoding(InputRegister::Encoding encoding);

		bool busy() const;

	signals:
		void valueChanged();

		void valueUpdated();

		void deviceChanged();

		void valueScaleChanged();

		void addressChanged();

		void encodingChanged();

		void busyChanged();

	protected slots:
		void onValueUpdated();

		void onInputRegisterDestroyed();

	protected:
		void setBusy(bool busy);

		void updateValue();

	private:
		void setupRegister(InputRegister * reg);

	private:
		AbstractDevice * m_device;
		int m_address;
		qreal m_value;
		qreal m_valueScale;
		InputRegister::Encoding m_encoding;
		bool m_busy;
		InputRegister * m_register;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
