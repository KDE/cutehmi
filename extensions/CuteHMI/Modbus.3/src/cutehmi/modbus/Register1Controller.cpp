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
	connect(this, & AbstractRegisterController::enabledChanged, this, & Register1Controller::resetRegister);
	connect(this, & Register1Controller::valueFailed, this, & Register1Controller::valueChanged);		// Trigger value dependent slots also in case of failed writes.
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
	if (enabled())
		Mixin::setValue(value);
}

void Register1Controller::writeValue()
{
	if (enabled())
		Mixin::writeValue();
}

void Register1Controller::timerEvent(QTimerEvent * event)
{
	if (enabled())
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
	} else if (m->value != m->requestedValue) {
		// Trigger value dependent slots also in case of mismatched writes.

		m->requestedValue = m->value;
		emit valueChanged();
	}

	emit valueUpdated();
}

void Register1Controller::updateValue(const QJsonValue & value)
{
	updateValue(value.toBool());
}

void Register1Controller::onRequestCompleted(QJsonObject request, QJsonObject reply)
{
	if (enabled())
		Mixin::onRequestCompleted(request, reply);
}

void Register1Controller::resetRegister()
{
	m->requestId = QUuid();	// Setting up new register invalidates previous requests.
	m->postponedWritePending = false;
	m->adjustingValue = false;

	if (m->register1)
		m->register1->rest();

	if (device()) {
		m->register1 = registerAt(static_cast<quint16>(address()));
		if (enabled()) {
			setBusy(true);
			m->register1->awake();
			updateValue();
		} else
			setBusy(false);
	} else
		m->register1 = nullptr;
}

void Register1Controller::requestWrite(bool value)
{
	setBusy(true);
	requestWriteRegister(static_cast<quint16>(address()), value, & m->requestId);
}

bool Register1Controller::verifyRegisterValue() const
{
	CUTEHMI_ASSERT(m->register1 != nullptr, "m->register1 can not be nullptr when calling this function");

	return m->register1->value() == m->requestedValue;
}

}
}

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
