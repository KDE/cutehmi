#include "HoldingRegisterController.hpp"

namespace cutehmi {
namespace modbus {
namespace qml {

HoldingRegisterController::HoldingRegisterController(QObject * parent):
	QObject(parent),
	m_device(nullptr),
	m_address(0),
	m_value(0.0),
	m_valueScale(1.0),
	m_encoding(HoldingRegister::INT16),
	m_busy(true),
	m_register(nullptr)
{
}

HoldingRegisterController::~HoldingRegisterController()
{
	setupRegister(nullptr);
}

AbstractDevice * HoldingRegisterController::device() const
{
	return m_device;
}

void HoldingRegisterController::setDevice(AbstractDevice * device)
{
	if (device != m_device) {
		m_device = device;
		if (m_device != nullptr)
			setupRegister(m_device->rAt(m_address));
		emit deviceChanged();
		updateValue();
	}
}

int HoldingRegisterController::address() const
{
	return m_address;
}

void HoldingRegisterController::setAddress(int address)
{
	if (m_address != address) {
		m_address = address;
		if (m_device != nullptr)
			setupRegister(m_device->rAt(m_address));
		emit addressChanged();
		updateValue();
	}
}

qreal HoldingRegisterController::value() const
{
	return m_value;
}

void HoldingRegisterController::setValue(qreal value)
{
	if ((m_register != nullptr) && (m_value != value))
		m_register->requestValue(value / m_valueScale, m_encoding);
}

qreal HoldingRegisterController::valueScale() const
{
	return m_valueScale;
}

void HoldingRegisterController::setValueScale(qreal valueScale)
{
	if (m_valueScale != valueScale) {
		m_valueScale = valueScale;
		emit valueScaleChanged();
	}
}

HoldingRegister::Encoding HoldingRegisterController::encoding() const
{
	return m_encoding;
}

void HoldingRegisterController::setEncoding(HoldingRegister::Encoding encoding)
{
	if (m_encoding != encoding) {
		m_encoding = encoding;
		emit encodingChanged();
	}
}

bool HoldingRegisterController::busy() const
{
	return m_busy;
}

void HoldingRegisterController::onValueRequested()
{
	setBusy(true);
}

void HoldingRegisterController::onValueUpdated()
{
	if (m_register->pendingRequests() > 0)
		return;

	updateValue();
	emit valueUpdated();
	setBusy(false);
}

void HoldingRegisterController::onHoldingRegisterDestroyed()
{
	m_register = nullptr;
}

void HoldingRegisterController::setBusy(bool busy)
{
	if (m_busy != busy) {
		m_busy = busy;
		emit busyChanged();
	}
}

void HoldingRegisterController::updateValue()
{
	if (m_register == nullptr)
		return;

	qreal newValue = m_valueScale * m_register->value(m_encoding).toReal();
	if (m_value != newValue) {
		m_value = newValue;
		emit valueChanged();
	}
}

void HoldingRegisterController::setupRegister(HoldingRegister * reg)
{
	if (m_register != nullptr) {
		disconnect(m_register, & HoldingRegister::valueUpdated, this, & HoldingRegisterController::onValueUpdated);
		disconnect(m_register, & HoldingRegister::valueRequested, this, & HoldingRegisterController::onValueRequested);
		disconnect(m_register, & HoldingRegister::destroyed, this, & HoldingRegisterController::onHoldingRegisterDestroyed);
		m_register->rest();
	}
	m_register = reg;
	if (m_register != nullptr) {
		connect(m_register, & HoldingRegister::valueUpdated, this, & HoldingRegisterController::onValueUpdated);
		connect(m_register, & HoldingRegister::valueRequested, this, & HoldingRegisterController::onValueRequested);
		connect(m_register, & HoldingRegister::destroyed, this, & HoldingRegisterController::onHoldingRegisterDestroyed);
		m_register->awake();
	}
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
