#include <cutehmi/modbus/Register1Controller.hpp>

#include <cutehmi/modbus/internal/functions.hpp>

#include <QTimerEvent>

namespace cutehmi {
namespace modbus {

constexpr bool Register1Controller::INITIAL_VALUE;

Register1Controller::Register1Controller(QObject * parent):
	AbstractRegisterController(parent),
	m(new Members)
{
	connect(this, & AbstractRegisterController::deviceChanged, this, & Register1Controller::resetRegister);
	connect(this, & AbstractRegisterController::addressChanged, this, & Register1Controller::resetRegister);
}

Register1Controller::~Register1Controller()
{
	setDevice(nullptr);
}

bool Register1Controller::value() const
{
	return m->value;
}

void Register1Controller::setValue(bool value)
{
	Mixin::setValue(value);
}

void Register1Controller::writeValue()
{
	Mixin::writeValue();
}

void Register1Controller::timerEvent(QTimerEvent * event)
{
	Mixin::timerEvent(event);
}

quint16 Register1Controller::bytes() const
{
	return 1;
}

void Register1Controller::onDeviceDestroyed()
{
	// References to coils/registers become invalid *before* device object emits destroyed() signal.
	m->register1 = nullptr;
}

void Register1Controller::updateValue()
{
	if (m->register1 == nullptr)
		return;

	updateValue(m->register1->value());
}

void Register1Controller::updateValue(bool value)
{
	// Do not update value if user is adjusting it.
	if (m->adjustingValue)
		return;

	if (m->value != value) {
		m->value = value;
		emit valueChanged();
	} else if (m->value != m->requestedValue)
		emit valueChanged();	// Trigger slots also in case of failed writes.

	emit valueUpdated();
}

void Register1Controller::updateValue(const QJsonValue & value)
{
	updateValue(value.toBool());
}

void Register1Controller::onRequestCompleted(QJsonObject request, QJsonObject reply)
{
	Mixin::onRequestCompleted(request, reply);
}

void Register1Controller::resetRegister()
{
	m->requestId = nullptr;	// Setting up new register invalidates previous requests.
	m->postponedWritePending = false;
	m->adjustingValue = false;

	if (m->register1)
		m->register1->rest();

	if (device()) {
		setBusy(true);
		m->register1 = registerAt(address());
		m->register1->awake();
		updateValue();
	} else
		m->register1 = nullptr;
}

void Register1Controller::requestWrite(bool value)
{
	setBusy(true);
	requestWriteRegister(address(), value, & m->requestId);
}

bool Register1Controller::verifyRegisterValue() const
{
	CUTEHMI_ASSERT(m->register1 != nullptr, "m->register1 can not be nullptr when calling this function");

	return m->register1->value() == m->value;
}

}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
