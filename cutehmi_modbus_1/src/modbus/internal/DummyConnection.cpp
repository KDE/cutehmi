#include "../../../include/modbus/internal/DummyConnection.hpp"

#include <QThread>

#include <algorithm>

namespace cutehmi {
namespace modbus {
namespace internal {

DummyConnection::DummyConnection():
	m(new Members)
{
}

void DummyConnection::setLatency(unsigned long latency)
{
	m->latency = latency;
}

unsigned long DummyConnection::latency() const
{
	return m->latency;
}

void DummyConnection::setConnectLatency(unsigned long latency)
{
	m->connectLatency = latency;
}

unsigned long DummyConnection::connectLatency() const
{
	return m->connectLatency;
}

void DummyConnection::setDisconnectLatency(unsigned long latency)
{
	m->disconnectLatency = latency;
}

unsigned long DummyConnection::disconnectLatency() const
{
	return m->disconnectLatency;
}

bool DummyConnection::connect()
{
	if (m->connected)
		return false;
	QThread::msleep(connectLatency());
	m->connected = true;
	return true;
}

void DummyConnection::disconnect()
{
	QThread::msleep(disconnectLatency());
	m->connected = false;
}

bool DummyConnection::connected() const
{
	return m->connected;
}

int DummyConnection::readIr(int addr, int num, uint16_t * dest)
{
	if (!m->connected) {
		CUTEHMI_LOG_DEBUG("Not connected.");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m->irArr + addr, num, dest);
	return num;
}

int DummyConnection::readR(int addr, int num, uint16_t * dest)
{
	if (!m->connected) {
		CUTEHMI_LOG_DEBUG("Not connected.");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m->rArr + addr, num, dest);
	return num;
}

int DummyConnection::writeR(int addr, uint16_t value)
{
	if (!m->connected) {
		CUTEHMI_LOG_DEBUG("Not connected.");
		return -1;
	}
	QThread::msleep(latency());
	m->rArr[addr] = value;
	return 1;
}

int DummyConnection::readIb(int addr, int num, bool * dest)
{
	if (!m->connected) {
		CUTEHMI_LOG_DEBUG("Not connected.");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m->ibArr + addr, num, dest);
	return num;
}

int DummyConnection::readB(int addr, int num, bool * dest)
{
	if (!m->connected) {
		CUTEHMI_LOG_DEBUG("Not connected.");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m->bArr + addr, num, dest);
	return num;
}

int DummyConnection::writeB(int addr, bool value)
{
	if (!m->connected) {
		CUTEHMI_LOG_DEBUG("Not connected.");
		return -1;
	}
	QThread::msleep(latency());
	m->bArr[addr] = value;
	return 1;
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
