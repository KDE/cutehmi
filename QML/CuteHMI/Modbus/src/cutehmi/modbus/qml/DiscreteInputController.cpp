#include "DiscreteInputController.hpp"

namespace cutehmi {
namespace modbus {
namespace qml {

DiscreteInputController::DiscreteInputController(QObject * parent):
	QObject(parent),
	m_device(nullptr),
	m_address(0),
	m_value(false),
	m_busy(true),
	m_input(nullptr)
{
}

DiscreteInputController::~DiscreteInputController()
{
	setupInput(nullptr);
}

AbstractDevice * DiscreteInputController::device() const
{
	return m_device;
}

void DiscreteInputController::setDevice(AbstractDevice * device)
{
	if (device != m_device) {
		m_device = device;
		if (m_device != nullptr)
			setupInput(m_device->ibAt(m_address));
		emit deviceChanged();
		updateValue();
	}
}

int DiscreteInputController::address() const
{
	return m_address;
}

void DiscreteInputController::setAddress(int address)
{
	if (m_address != address) {
		m_address = address;
		if (m_device != nullptr)
			setupInput(m_device->ibAt(m_address));
		emit addressChanged();
		updateValue();
	}
}

bool DiscreteInputController::value() const
{
	return m_value;
}

bool DiscreteInputController::busy() const
{
	return m_busy;
}

void DiscreteInputController::onValueUpdated()
{
	updateValue();
	emit valueUpdated();
	setBusy(false);
}

void DiscreteInputController::onDiscreteInputDestroyed()
{
	m_input = nullptr;
}

void DiscreteInputController::setBusy(bool busy)
{
	if (m_busy != busy) {
		m_busy = busy;
		emit busyChanged();
	}
}

void DiscreteInputController::updateValue()
{
	if (m_input == nullptr)
		return;

	if (m_value != m_input->value()) {
		m_value = m_input->value();
		emit valueChanged();
	}
}

void DiscreteInputController::setupInput(DiscreteInput * input)
{
	if (m_input != nullptr) {
		disconnect(m_input, & DiscreteInput::valueUpdated, this, & DiscreteInputController::onValueUpdated);
		disconnect(m_input, & DiscreteInput::destroyed, this, & DiscreteInputController::onDiscreteInputDestroyed);
		m_input->rest();
	}
	m_input = input;
	if (m_input != nullptr) {
		connect(m_input, & DiscreteInput::valueUpdated, this, & DiscreteInputController::onValueUpdated);
		connect(m_input, & DiscreteInput::destroyed, this, & DiscreteInputController::onDiscreteInputDestroyed);
		m_input->awake();
	}
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
