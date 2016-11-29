#include "DummyConnection.hpp"

#include <QThread>

#include <algorithm>

namespace cutehmi {
namespace modbus {

DummyConnection::DummyConnection():
	m_connected(false),
	m_latency(0),
	m_rArr(),
	m_irArr(),
	m_bArr(),
	m_ibArr()
{
}


void DummyConnection::setLatency(unsigned long latency)
{
	m_latency = latency;
}

unsigned long DummyConnection::latency() const
{
	return m_latency;
}

bool DummyConnection::connect()
{
	if (m_connected)
		return false;
	m_connected = true;
	return true;
}

void DummyConnection::disconnect()
{
	m_connected = false;
}

int DummyConnection::readIr(int addr, int num, uint16_t * dest)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m_irArr + addr, num, dest);
	return num;
}

int DummyConnection::readR(int addr, int num, uint16_t * dest)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m_rArr + addr, num, dest);
	return num;
}

int DummyConnection::writeR(int addr, uint16_t value)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	m_rArr[addr] = value;
	return 1;
}

int DummyConnection::readIb(int addr, int num, bool * dest)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m_ibArr + addr, num, dest);
	return num;
}

int DummyConnection::readB(int addr, int num, bool * dest)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m_bArr + addr, num, dest);
	return num;
}

int DummyConnection::writeB(int addr, bool value)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	m_bArr[addr] = value;
	return 1;
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
