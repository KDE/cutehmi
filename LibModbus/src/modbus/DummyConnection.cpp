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

int DummyConnection::readIr(int addr, int num, uint16_t * dst)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m_irArr + addr, num, dst);
	return num;
}

int DummyConnection::readR(int addr, int num, uint16_t * dst)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	std::copy_n(m_rArr + addr, num, dst);
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

int DummyConnection::readIb(int addr, int num, uint8_t * dst)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());

	int result = num;
	uint8_t * src = & m_bArr[addr / 8];
	uint8_t srcMask = 0x01 << addr % 8;
	uint8_t dstMask = 0x01;
	// Copy bit by bit.
	while (num > 0) {
		if (srcMask == 0) {
			srcMask = 0x01;
			src++;
		}
		if (dstMask == 0) {
			dstMask = 0x01;
			dst++;
		}
		*dst &= ~dstMask;
		if (*src & srcMask)
			*dst |= dstMask;
		srcMask <<= 1;
		dstMask <<= 1;
		num--;
	}

	return result;
}

int DummyConnection::readB(int addr, int num, uint8_t * dst)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());

	int result = num;
	uint8_t * src = & m_bArr[addr / 8];
	uint8_t srcMask = 0x01 << addr % 8;
	uint8_t dstMask = 0x01;
	// Copy bit by bit.
	while (num > 0) {
		if (srcMask == 0) {
			srcMask = 0x01;
			src++;
		}
		if (dstMask == 0) {
			dstMask = 0x01;
			dst++;
		}
		*dst &= ~dstMask;
		if (*src & srcMask)
			*dst |= dstMask;
		srcMask <<= 1;
		dstMask <<= 1;
		num--;
	}

	return result;
}

int DummyConnection::writeB(int addr, bool value)
{
	if (!m_connected) {
		qDebug("not connected");
		return -1;
	}
	QThread::msleep(latency());
	m_bArr[addr / 8] = (m_bArr[addr / 8] & ~(uint8_t(1) << addr % 8)) | (static_cast<uint8_t>(value) << addr % 8);
	return 1;
}

}
}
