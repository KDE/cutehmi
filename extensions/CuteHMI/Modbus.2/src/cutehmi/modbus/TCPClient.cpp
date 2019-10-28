#include <cutehmi/modbus/TCPClient.hpp>

namespace cutehmi {
namespace modbus {

constexpr int TCPClient::MIN_SLAVE_ADDRESS;
constexpr int TCPClient::MAX_SLAVE_ADDRESS;
const char * TCPClient::INITIAL_HOST = internal::TCPClientConfig::INITIAL_HOST;
constexpr int TCPClient::INITIAL_PORT;
constexpr int TCPClient::INITIAL_SLAVE_ADDRESS;

TCPClient::TCPClient(QObject * parent):
	AbstractClient(parent),
	m(new Members)
{
	m->backend.moveToThread(& m->thread);

	connect(& m->thread, & QThread::finished, & m->backend, & internal::QtClientBackend::ensureClosed);

	connect(this, & TCPClient::requestReceived, & m->backend, & internal::QtClientBackend::processRequest);

	connect(& m->backend, & internal::QtClientBackend::replied, this, & TCPClient::handleReply);

	connect(& m->backend, & internal::QtClientBackend::stateChanged, this, & TCPClient::setState);

	connect(& m->backend, & internal::QtClientBackend::closed, this, & TCPClient::stopped);

	connect(& m->backend, & internal::QtClientBackend::opened, this, & TCPClient::started);

	connect(& m->backend, & internal::QtClientBackend::errored, this, & TCPClient::broke);
	connect(& m->backend, & internal::QtClientBackend::closed, this, & TCPClient::broke);

	m->thread.start();
}

TCPClient::~TCPClient()
{
	m->thread.quit();
	m->thread.wait();
}

QString TCPClient::host() const
{
	return m->config.host();
}

void TCPClient::setHost(const QString & host)
{
	if (m->config.host() != host) {
		m->config.setHost(host);
		emit hostChanged();
	}
}

int TCPClient::port() const
{
	return m->config.port();
}

void TCPClient::setPort(int port)
{
	if (m->config.port() != port) {
		m->config.setPort(port);
		emit portChanged();
	}
}

int TCPClient::slaveAddress() const
{
	return m->config.slaveAddress();
}

void TCPClient::setSlaveAddress(int slaveAddress)
{
	if (m->config.slaveAddress() != slaveAddress) {
		m->config.setSlaveAddress(slaveAddress);
		emit slaveAddressChanged();
	}
}

void TCPClient::open()
{
	emit m->backend.openRequested();
}

void TCPClient::close()
{
	emit m->backend.closeRequested();
}

}
}

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
