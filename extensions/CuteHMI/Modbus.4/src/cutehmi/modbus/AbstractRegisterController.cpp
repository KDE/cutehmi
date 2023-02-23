#include "AbstractRegisterController.hpp"
#include "internal/functions.hpp"

namespace cutehmi {
namespace modbus {

constexpr unsigned int AbstractRegisterController::INITIAL_ADDRESS;
constexpr bool AbstractRegisterController::INITIAL_BUSY;
constexpr bool AbstractRegisterController::INITIAL_READ_ON_WRITE;
constexpr AbstractRegisterController::WriteMode AbstractRegisterController::INITIAL_WRITE_MODE;
constexpr int AbstractRegisterController::INITIAL_WRITE_DELAY;
constexpr bool AbstractRegisterController::INITIAL_ENABLED;

AbstractRegisterController::AbstractRegisterController(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

AbstractDevice * AbstractRegisterController::device() const
{
	return m->device;
}

void AbstractRegisterController::setDevice(AbstractDevice * device)
{
	if (device != m->device) {
		if (m->device != nullptr)
			m->device->disconnect(this);
		m->device = device;
		if (m->device != nullptr) {
			connect(m->device, & AbstractDevice::requestCompleted, this, & AbstractRegisterController::onRequestCompleted);
			connect(m->device, & AbstractDevice::readyChanged, this, [this]() {
				if (!m->device->ready())
					setBusy(true);
			});
			connect(m->device, & QObject::destroyed, this, [this]() {
				onDeviceDestroyed();
				setDevice(nullptr);
			});
			connect(m->device, & AbstractDevice::readyChanged, this, [this]() {
				if (deviceReady() && enabled())
					requestReadRegisters(static_cast<quint16>(address()), bytes(), nullptr);
			});
			if (!m->deferRequestRead && deviceReady() && enabled())
				requestReadRegisters(static_cast<quint16>(address()), bytes(), nullptr);
		}
		emit deviceChanged();
	}
}

unsigned int AbstractRegisterController::address() const
{
	return m->address;
}

void AbstractRegisterController::setAddress(unsigned int address)
{
	if (m->address != address) {
		m->address = address;
		if (!m->deferRequestRead && deviceReady() && enabled())
			requestReadRegisters(static_cast<quint16>(address), bytes(), nullptr);
		emit addressChanged();
	}
}

bool AbstractRegisterController::busy() const
{
	return m->busy;
}

bool AbstractRegisterController::readOnWrite() const
{
	return m->readOnWrite;
}

void AbstractRegisterController::setReadOnWrite(bool readOnWrite)
{
	if (m->readOnWrite != readOnWrite) {
		m->readOnWrite = readOnWrite;
		emit readOnWriteChanged();
	}
}

AbstractRegisterController::WriteMode AbstractRegisterController::writeMode() const
{
	return m->writeMode;
}

void AbstractRegisterController::setWriteMode(AbstractRegisterController::WriteMode writeMode)
{
	if (m->writeMode != writeMode) {
		m->writeMode = writeMode;
		emit writeModeChanged();
	}
}

int AbstractRegisterController::writeDelay() const
{
	return m->writeDelay;
}

void AbstractRegisterController::setWriteDelay(int writeDelay)
{
	if (m->writeDelay != writeDelay) {
		m->writeDelay = writeDelay;
		emit writeDelayChanged();
	}
}

bool AbstractRegisterController::enabled() const
{
	return m->enabled;
}

void AbstractRegisterController::setEnabled(bool enabled)
{
	if (m->enabled != enabled) {
		m->enabled = enabled;
		emit enabledChanged();
	}
}

void AbstractRegisterController::classBegin()
{
	m->deferRequestRead = true;
}

void AbstractRegisterController::componentComplete()
{
	m->deferRequestRead = false;

	if (deviceReady() && enabled())
		requestReadRegisters(static_cast<quint16>(address()), bytes(), nullptr);
}

void AbstractRegisterController::setBusy(bool busy)
{
	if (m->busy != busy) {
		m->busy = busy;
		emit busyChanged();
	}
}

bool AbstractRegisterController::deviceReady() const
{
	return (m->device != nullptr) && m->device->ready();
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
