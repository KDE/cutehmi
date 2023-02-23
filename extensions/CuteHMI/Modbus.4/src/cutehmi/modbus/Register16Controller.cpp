#include "Register16Controller.hpp"

#include <QTimerEvent>

namespace cutehmi {
namespace modbus {

constexpr qreal Register16Controller::INITIAL_VALUE;
constexpr qreal Register16Controller::INITIAL_VALUE_SCALE;
constexpr Register16Controller::Encoding Register16Controller::INITIAL_ENCODING;

Register16Controller::Register16Controller(QObject * parent):
	AbstractRegisterController(parent),
	m(new Members)
{
	connect(this, & AbstractRegisterController::deviceChanged, this, & Register16Controller::resetRegister);
	connect(this, & AbstractRegisterController::addressChanged, this, & Register16Controller::resetRegister);
	connect(this, & AbstractRegisterController::enabledChanged, this, & Register16Controller::resetRegister);
	connect(this, & Register16Controller::valueFailed, this, & Register16Controller::valueChanged);		// Trigger value dependent slots also in case of failed writes.
}

Register16Controller::~Register16Controller()
{
	setDevice(nullptr);
}

qreal Register16Controller::value() const
{
	return m->value;
}

void Register16Controller::setValue(qreal value)
{
	if (enabled())
		Mixin::setValue(value);
}

qreal Register16Controller::valueScale() const
{
	return m->valueScale;
}

void Register16Controller::setValueScale(qreal valueScale)
{
	if (m->valueScale != valueScale) {
		m->valueScale = valueScale;
		emit valueScaleChanged();
		updateValue();
	}
}

Register16Controller::Encoding Register16Controller::encoding() const
{
	return m->encoding;
}

void Register16Controller::setEncoding(Encoding encoding)
{
	if (m->encoding != encoding) {
		m->encoding = encoding;
		emit encodingChanged();
		updateValue();
	}
}

void Register16Controller::writeValue()
{
	if (enabled())
		Mixin::writeValue();
}

void Register16Controller::timerEvent(QTimerEvent * event)
{
	if (enabled())
		Mixin::timerEvent(event);
}

quint16 Register16Controller::bytes() const
{
	return 1;
}

void Register16Controller::onDeviceDestroyed()
{
	// References to coils/registers become invalid *before* device object emits destroyed() signal.
	m->register16 = nullptr;
}

void Register16Controller::updateValue()
{
	if (m->register16 == nullptr)
		return;

	updateValue(m->register16->value());
}

void Register16Controller::updateValue(quint16 value)
{
	// Do not update value if user is adjusting it, because it could distract user.
	if (m->adjustingValue)
		return;

//	qWarning() << "val " << m->value << " req val " << m->requestedValue << " " << (m->value == m->requestedValue);
	qreal newValue = m->valueScale * Decode(value, encoding());
	if (m->value != newValue) {
		m->value = newValue;
		emit valueChanged();
	} else if (m->value != m->requestedValue) {
		// Trigger value dependent slots also in case of mismatched writes.

		m->requestedValue = m->value;
		emit valueChanged();
	}

	emit valueUpdated();
}

void Register16Controller::updateValue(const QJsonValue & value)
{
	updateValue(static_cast<quint16>(value.toDouble()));
}

void Register16Controller::onRequestCompleted(QJsonObject request, QJsonObject reply)
{
	if (enabled())
		Mixin::onRequestCompleted(request, reply);
}

void Register16Controller::resetRegister()
{
	m->requestId = QUuid();	// Setting up new register invalidates previous requests.
	m->postponedWritePending = false;
	m->adjustingValue = false;

	if (m->register16)
		m->register16->rest();

	if (device()) {
		m->register16 = registerAt(static_cast<quint16>(address()));
		if (enabled()) {
			setBusy(true);
			m->register16->awake();
			updateValue();
		} else
			setBusy(false);
	} else
		m->register16 = nullptr;
}

qreal Register16Controller::Decode(quint16 value, Encoding encoding)
{
	CUTEHMI_ASSERT(encoding == INT16 || encoding == UINT16,
			QString("unrecognized encoding ('%1')").arg(encoding).toLocal8Bit().constData());

	switch (encoding) {
		case UINT16:
			return value;
		case INT16:
			return internal::int16FromUint16(value);
	}
	return std::numeric_limits<qreal>::quiet_NaN();
}

quint16 Register16Controller::Encode(qreal value, Encoding encoding)
{
	CUTEHMI_ASSERT(encoding == INT16 || encoding == UINT16,
			QString("unrecognized encoding ('%1')").arg(encoding).toLocal8Bit().constData());

	switch (encoding) {
		case UINT16:
			return static_cast<quint16>(qRound64(value));
		case INT16:
			return internal::int16ToUint16(static_cast<qint16>(qRound(value))); // Note: int (as returned by qRound()) is guaranteed to be at least 16 bits wide by a standard.
	}
	return 0;
}

bool Register16Controller::ValidateEncoding(qreal value, Encoding encoding)
{
	CUTEHMI_ASSERT(encoding == INT16 || encoding == UINT16,
			QString("unrecognized encoding ('%1')").arg(encoding).toLocal8Bit().constData());

	switch (encoding) {
		case UINT16:
			return qRound64(value) <= std::numeric_limits<quint16>::max() && qRound64(value) >= std::numeric_limits<quint16>::min();
		case INT16:
			// Note: int (as returned by qRound()) is guaranteed to be at least 16 bits wide by a standard.
			return qRound(value) <= std::numeric_limits<qint16>::max() && qRound(value) >= std::numeric_limits<qint16>::min();
	}
	return false;
}

void Register16Controller::requestWrite(qreal value)
{
	qreal scaledValue = value / m->valueScale;
	if (ValidateEncoding(scaledValue, encoding())) {
		setBusy(true);
		requestWriteRegister(static_cast<quint16>(address()), Encode(scaledValue, encoding()), & m->requestId);
	} else {
		CUTEHMI_CRITICAL("Can not represent requested value '" << scaledValue << "' using selected encoding '" << encoding() << "'.");
		emit valueFailed();
	}
}

bool Register16Controller::verifyRegisterValue() const
{
	CUTEHMI_ASSERT(m->register16 != nullptr, "m->register16 can not be nullptr when calling this function");

	return Decode(m->register16->value(), encoding()) == m->requestedValue;
}

}
}

//(c)C: Copyright © 2022-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
