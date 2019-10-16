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
				if (m->device->ready())
					requestReadRegisters(address(), bytes(), nullptr);
			});
			if (!m->deferRequestRead && m->device->ready())
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
		if (!m->deferRequestRead && m->device->ready())
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

	if (m->device->ready())
		requestReadRegisters(address(), bytes(), nullptr);
}

void AbstractRegisterController::setBusy(bool busy)
{
	if (m->busy != busy) {
		m->busy = busy;
		emit busyChanged();
	}
}

}
}
