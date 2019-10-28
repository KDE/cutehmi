#include <cutehmi/modbus/internal/RTUClientConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

RTUClientConfig::RTUClientConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString RTUClientConfig::port() const
{
	QReadLocker locker(& m->lock);

	return m->port;
}

void RTUClientConfig::setPort(const QString & port)
{
	QWriteLocker locker(& m->lock);

	m->port = port;

	emit configChanged();
}

QSerialPort::Parity RTUClientConfig::parity() const
{
	QReadLocker locker(& m->lock);

	return m->parity;
}

void RTUClientConfig::setParity(QSerialPort::Parity parity)
{
	QWriteLocker locker(& m->lock);

	m->parity = parity;

	emit configChanged();
}

QSerialPort::BaudRate RTUClientConfig::baudRate() const
{
	QReadLocker locker(& m->lock);

	return m->baudRate;
}

void RTUClientConfig::setBaudRate(QSerialPort::BaudRate baudRate)
{
	QWriteLocker locker(& m->lock);

	m->baudRate = baudRate;

	emit configChanged();
}

QSerialPort::DataBits RTUClientConfig::dataBits() const
{
	QReadLocker locker(& m->lock);

	return m->dataBits;
}

void RTUClientConfig::setDataBits(QSerialPort::DataBits dataBits)
{
	QWriteLocker locker(& m->lock);

	m->dataBits = dataBits;

	emit configChanged();
}

QSerialPort::StopBits RTUClientConfig::stopBits() const
{
	QReadLocker locker(& m->lock);

	return m->stopBits;
}

void RTUClientConfig::setStopBits(QSerialPort::StopBits stopBits)
{
	QWriteLocker locker(& m->lock);

	m->stopBits = stopBits;

	emit configChanged();
}

int RTUClientConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);

	return m->slaveAddress;
}

void RTUClientConfig::setSlaveAddress(int slaveId)
{
	QWriteLocker locker(& m->lock);

	m->slaveAddress = slaveId;

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
