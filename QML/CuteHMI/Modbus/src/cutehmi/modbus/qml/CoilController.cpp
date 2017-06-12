#include "CoilController.hpp"

namespace cutehmi {
namespace modbus {
namespace qml {

CoilController::CoilController(QObject * parent):
	QObject(parent),
	m_device(nullptr),
	m_address(0),
	m_value(false),
	m_busy(true),
	m_coil(nullptr)
{
}

CoilController::~CoilController()
{
	setupCoil(nullptr);
}

AbstractDevice * CoilController::device() const
{
	return m_device;
}

void CoilController::setDevice(AbstractDevice * device)
{
	if (device != m_device) {
		m_device = device;
		if (m_device != nullptr)
			setupCoil(m_device->bAt(m_address));
		emit deviceChanged();
		updateValue();
	}
}

int CoilController::address() const
{
	return m_address;
}

void CoilController::setAddress(int address)
{
	if (m_address != address) {
		m_address = address;
		if (m_device != nullptr)
			setupCoil(m_device->bAt(m_address));
		emit addressChanged();
		updateValue();
	}
}

bool CoilController::value() const
{
	return m_value;
}

void CoilController::setValue(bool value)
{
	if ((m_coil != nullptr) && (m_value != value))
		m_coil->requestValue(value);
}

bool CoilController::busy() const
{
	return m_busy;
}

void CoilController::onValueRequested()
{
	setBusy(true);
}

void CoilController::onValueUpdated()
{
	if (m_coil->pendingRequests() > 0)
		return;

	updateValue();
	emit valueUpdated();
	setBusy(false);
}

void CoilController::setBusy(bool busy)
{
	if (m_busy != busy) {
		m_busy = busy;
		emit busyChanged();
	}
}

void CoilController::updateValue()
{
	if (m_coil == nullptr)
		return;

	if (m_value != m_coil->value()) {
		m_value = m_coil->value();
		emit valueChanged();
	}
}

void CoilController::setupCoil(Coil * reg)
{
	if (m_coil != nullptr) {
		disconnect(m_coil, & Coil::valueUpdated, this, & CoilController::onValueUpdated);
		disconnect(m_coil, & Coil::valueRequested, this, & CoilController::onValueRequested);
		m_coil->rest();
	}
	m_coil = reg;
	if (m_coil != nullptr) {
		connect(m_coil, & Coil::valueUpdated, this, & CoilController::onValueUpdated);
		connect(m_coil, & Coil::valueRequested, this, & CoilController::onValueRequested);
		m_coil->awake();
	}
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
