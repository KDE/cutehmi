#include <cutehmi/modbus/internal/RTUServerConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

RTUServerConfig::RTUServerConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString RTUServerConfig::port() const
{
	QReadLocker locker(& m->lock);

	return m->port;
}

void RTUServerConfig::setPort(const QString & port)
{
	QWriteLocker locker(& m->lock);

	m->port = port;

	emit configChanged();
}

QSerialPort::Parity RTUServerConfig::parity() const
{
	QReadLocker locker(& m->lock);

	return m->parity;
}

void RTUServerConfig::setParity(QSerialPort::Parity parity)
{
	QWriteLocker locker(& m->lock);

	m->parity = parity;

	emit configChanged();
}

QSerialPort::BaudRate RTUServerConfig::baudRate() const
{
	QReadLocker locker(& m->lock);

	return m->baudRate;
}

void RTUServerConfig::setBaudRate(QSerialPort::BaudRate baudRate)
{
	QWriteLocker locker(& m->lock);

	m->baudRate = baudRate;

	emit configChanged();
}

QSerialPort::DataBits RTUServerConfig::dataBits() const
{
	QReadLocker locker(& m->lock);

	return m->dataBits;
}

void RTUServerConfig::setDataBits(QSerialPort::DataBits dataBits)
{
	QWriteLocker locker(& m->lock);

	m->dataBits = dataBits;

	emit configChanged();
}

QSerialPort::StopBits RTUServerConfig::stopBits() const
{
	QReadLocker locker(& m->lock);

	return m->stopBits;
}

void RTUServerConfig::setStopBits(QSerialPort::StopBits stopBits)
{
	QWriteLocker locker(& m->lock);

	m->stopBits = stopBits;

	emit configChanged();
}

int cutehmi::modbus::internal::RTUServerConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);
	return m->slaveAddress;
}

void RTUServerConfig::setSlaveAddress(int address)
{
	QWriteLocker locker(& m->lock);
	m->slaveAddress = address;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::coilsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->coilsAddressRange;
}

void RTUServerConfig::setCoilsAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->coilsAddressRange = addressRange;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::inputRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->inputRegistersAddressRange;
}

void RTUServerConfig::setInputRegistersAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->inputRegistersAddressRange = addressRange;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::discreteInputsAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->discreteInputsAddressRange;
}

void RTUServerConfig::setDiscreteInputsAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->discreteInputsAddressRange = addressRange;
	emit configChanged();
}

RTUServerConfig::AddressRange RTUServerConfig::holdingRegistersAddressRange() const
{
	QReadLocker locker(& m->lock);
	return m->holdingRegistersAddressRange;
}

void RTUServerConfig::setHoldingRegistersAddressRange(RTUServerConfig::AddressRange addressRange)
{
	QWriteLocker locker(& m->lock);
	m->holdingRegistersAddressRange = addressRange;
	emit configChanged();
}

}
}
}

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
