#include "InputRegisterController.hpp"

namespace cutehmi {
namespace modbus {
namespace qml {

InputRegisterController::InputRegisterController(QObject * parent):
	QObject(parent),
	m_device(nullptr),
	m_address(0),
	m_value(0.0),
	m_valueScale(1.0),
	m_encoding(InputRegister::INT16),
	m_busy(true),
	m_register(nullptr)
{
}

InputRegisterController::~InputRegisterController()
{
	setupRegister(nullptr);
}

cutehmi::modbus::AbstractDevice * InputRegisterController::device() const
{
	return m_device;
}

void InputRegisterController::setDevice(cutehmi::modbus::AbstractDevice * device)
{
	if (device != m_device) {
		m_device = device;
		if (m_device != nullptr)
			setupRegister(m_device->irAt(m_address));
		emit deviceChanged();
		updateValue();
	}
}

int InputRegisterController::address() const
{
	return m_address;
}

void InputRegisterController::setAddress(int address)
{
	if (m_address != address) {
		m_address = address;
		if (m_device != nullptr)
			setupRegister(m_device->irAt(m_address));
		emit addressChanged();
		updateValue();
	}
}

qreal InputRegisterController::value() const
{
	return m_value;
}

qreal InputRegisterController::valueScale() const
{
	return m_valueScale;
}

void InputRegisterController::setValueScale(qreal valueScale)
{
	if (m_valueScale != valueScale) {
		m_valueScale = valueScale;
		emit valueScaleChanged();
	}
}

InputRegister::encoding_t InputRegisterController::encoding() const
{
	return m_encoding;
}

void InputRegisterController::setEncoding(InputRegister::encoding_t encoding)
{
	if (m_encoding != encoding) {
		m_encoding = encoding;
		emit encodingChanged();
	}
}

bool InputRegisterController::busy() const
{
	return m_busy;
}

void InputRegisterController::onValueUpdated()
{
	updateValue();
	setBusy(false);
}

void InputRegisterController::setBusy(bool busy)
{
	if (m_busy != busy) {
		m_busy = busy;
		emit busyChanged();
	}
}

void InputRegisterController::updateValue()
{
	if (m_register == nullptr)
		return;

	qreal newValue = m_valueScale * m_register->value(m_encoding).toReal();
	if (m_value != newValue) {
		m_value = newValue;
		emit valueChanged();
	}
}

void InputRegisterController::setupRegister(cutehmi::modbus::InputRegister * reg)
{
	if (m_register != nullptr) {
		disconnect(m_register, & InputRegister::valueUpdated, this, & InputRegisterController::onValueUpdated);
		m_register->rest();
	}
	m_register = reg;
	if (m_register != nullptr) {
		connect(m_register, & InputRegister::valueUpdated, this, & InputRegisterController::onValueUpdated);
		m_register->awake();
	}
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
