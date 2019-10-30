#include <cutehmi/modbus/internal/TCPClientConfig.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

constexpr int TCPClientConfig::MIN_SLAVE_ADDRESS;
constexpr int TCPClientConfig::MAX_SLAVE_ADDRESS;
const char * TCPClientConfig::INITIAL_HOST = "localhost";
constexpr int TCPClientConfig::INITIAL_PORT;
constexpr int TCPClientConfig::INITIAL_SLAVE_ADDRESS;

TCPClientConfig::TCPClientConfig(QObject * parent):
	Config(parent),
	m(new Members)
{
}

QString cutehmi::modbus::internal::TCPClientConfig::host() const
{
	QReadLocker locker(& m->lock);

	return m->host;
}

void TCPClientConfig::setHost(const QString & host)
{
	QWriteLocker locker(& m->lock);

	m->host = host;

	emit configChanged();
}

int cutehmi::modbus::internal::TCPClientConfig::port() const
{
	QReadLocker locker(& m->lock);

	return m->port;
}

void cutehmi::modbus::internal::TCPClientConfig::setPort(int port)
{
	QWriteLocker locker(& m->lock);

	m->port = port;

	emit configChanged();
}

int TCPClientConfig::slaveAddress() const
{
	QReadLocker locker(& m->lock);

	return m->slaveAddress;
}

void TCPClientConfig::setSlaveAddress(int slaveAddress)
{
	QWriteLocker locker(& m->lock);

	m->slaveAddress = slaveAddress;

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
