#include <cutehmi/modbus/AbstractRegisterController.hpp>

#include <cutehmi/modbus/internal/functions.hpp>

namespace cutehmi {
namespace modbus {

constexpr quint16 AbstractRegisterController::INITIAL_ADDRESS;
constexpr bool AbstractRegisterController::INITIAL_BUSY;
constexpr bool AbstractRegisterController::INITIAL_READ_ON_WRITE;
constexpr AbstractRegisterController::WriteMode AbstractRegisterController::INITIAL_WRITE_MODE;
constexpr int AbstractRegisterController::INITIAL_WRITE_DELAY;

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
				if (deviceReady())
					requestReadRegisters(address(), bytes(), nullptr);
			});
			if (!m->deferRequestRead && deviceReady())
				requestReadRegisters(address(), bytes(), nullptr);

		}
		emit deviceChanged();
	}
}

quint16 AbstractRegisterController::address() const
{
	return m->address;
}

void AbstractRegisterController::setAddress(quint16 address)
{
	if (m->address != address) {
		m->address = address;
		if (!m->deferRequestRead && deviceReady())
			requestReadRegisters(address, bytes(), nullptr);
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

void AbstractRegisterController::classBegin()
{
	m->deferRequestRead = true;
}

void AbstractRegisterController::componentComplete()
{
	m->deferRequestRead = false;

	if (deviceReady())
		requestReadRegisters(address(), bytes(), nullptr);
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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
