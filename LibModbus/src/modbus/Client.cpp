#include "Client.hpp"
#include "AbstractConnection.hpp"
#include "Exception.hpp"
#include "functions.hpp"

#include <QtDebug>
#include <QMutexLocker>
#include <QtConcurrent>

namespace cutehmi {
namespace modbus {

QString Client::Error::str() const
{
	switch (code()) {
		case Error::UNABLE_TO_CONNECT:
			return tr("Unable to connect.");
		default:
			return base::Error::str();
	}
}

Client::Client(std::unique_ptr<AbstractConnection> connection, QObject * parent):
	QObject(parent),
	m_ir(this, & m_irData, Client::Count<InputRegister>, Client::IrAt),
	m_r(this, & m_rData, Client::Count<HoldingRegister>, Client::RAt),
	m_ib(this, & m_ibData, Client::Count<DiscreteInput>, Client::IbAt),
	m_b(this, & m_bData, Client::Count<Coil>, Client::BAt),
	m_connection(std::move(connection)),
	m_endianness(INITIAL_ENDIANNESS),
	m_rValueRequestMapper(new QSignalMapper(this)),
	m_bValueRequestMapper(new QSignalMapper(this))
{
	QObject::connect(m_rValueRequestMapper, SIGNAL(mapped(int)), this, SLOT(rValueRequest(int)));
	QObject::connect(m_bValueRequestMapper, SIGNAL(mapped(int)), this, SLOT(bValueRequest(int)));
}

Client::~Client()
{
	QThreadPool::globalInstance()->waitForDone();

	for (IrDataContainer::KeysContainer::const_iterator it = m_irData.keys().begin(); it != m_irData.keys().end(); ++it)
		delete m_irData.at(*it);
	m_irData.clear();
	for (RDataContainer::KeysContainer::const_iterator it = m_rData.keys().begin(); it != m_rData.keys().end(); ++it)
		delete m_rData.at(*it);
	m_rData.clear();
	for (IbDataContainer::KeysContainer::const_iterator it = m_ibData.keys().begin(); it != m_ibData.keys().end(); ++it)
		delete m_ibData.at(*it);
	m_ibData.clear();
	for (BDataContainer::KeysContainer::const_iterator it = m_bData.keys().begin(); it != m_bData.keys().end(); ++it)
		delete m_bData.at(*it);
	m_bData.clear();
}

void Client::setEndianness(endianness_t endianness)
{
	m_endianness = endianness;
}

Client::endianness_t Client::endianness() const
{
	return m_endianness;
}

const QQmlListProperty<InputRegister> & Client::ir() const
{
	return m_ir;
}

const QQmlListProperty<HoldingRegister> & Client::r() const
{
	return m_r;
}

const QQmlListProperty<DiscreteInput> & Client::ib() const
{
	return m_ib;
}

const QQmlListProperty<Coil> & Client::b() const
{
	return m_b;
}

void Client::readIr(int addr)
{
	static const int NUM_READ = 1;

	QMutexLocker locker(& m_irMutex);
	IrDataContainer::iterator it = m_irData.find(addr);
	Q_ASSERT_X(it != m_irData.end(), __func__, "register has not been referenced yet");
	uint16_t val;
	qDebug() << "Reading value from input register " << addr << ".";
	if (m_connection->readIr(addr, NUM_READ, & val) != NUM_READ)
		qWarning() << tr("Failed reading input register value from the device.");
	else
		(*it)->updateValue(val); // libmodbus seems to take care about endianness, so fromClientEndian(val) is not necessary.
}

void Client::readR(int addr)
{
	static const int NUM_READ = 1;

	QMutexLocker locker(& m_rMutex);
	RDataContainer::iterator it = m_rData.find(addr);
	Q_ASSERT_X(it != m_rData.end(), __func__, "register has not been referenced yet");
	uint16_t val;
	qDebug() << "Reading value from holding register " << addr << ".";
	if (m_connection->readR(addr, NUM_READ, & val) != NUM_READ)
		qWarning() << tr("Failed reading register value from the device.");
	else
		(*it)->updateValue(val); // libmodbus seems to take care about endianness, so fromClientEndian(val) is not necessary.
}

void Client::writeR(int addr)
{
	QMutexLocker locker(& m_rMutex);
	RDataContainer::iterator it = m_rData.find(addr);
	Q_ASSERT_X(it != m_rData.end(), __func__, "register has not been referenced yet");
	uint16_t val = (*it)->requestedValue();
	qDebug() << "Writing requested value (" << val << ") to holding register " << addr << ".";
	if (m_connection->writeR(addr, val) != 1)
		qWarning() << tr("Failed to write register value to the device.");
	else
		emit (*it)->valueWritten();
}

void Client::readIb(int addr)
{
	static const int NUM_READ = 1;

	QMutexLocker locker(& m_ibMutex);
	IbDataContainer::iterator it = m_ibData.find(addr);
	Q_ASSERT_X(it != m_ibData.end(), __func__, "discrete input has not been referenced yet");
	bool val = 0;
	qDebug() << "Reading value from discrete input " << addr << ".";
	if (m_connection->readIb(addr, NUM_READ, & val) != NUM_READ)
		qWarning() << tr("Failed reading discrete input value from the device.");
	else
		(*it)->updateValue(val);
}

void Client::readB(int addr)
{
	static const int NUM_READ = 1;

	QMutexLocker locker(& m_bMutex);
	BDataContainer::iterator it = m_bData.find(addr);
	Q_ASSERT_X(it != m_bData.end(), __func__, "coil has not been referenced yet");
	bool val = 0;
	qDebug() << "Reading value from coil " << addr << ".";
	if (m_connection->readB(addr, NUM_READ, & val) != NUM_READ)
		qWarning() << tr("Failed reading coil value from the device.");
	else
		(*it)->updateValue(val);
}

void Client::writeB(int addr)
{
	QMutexLocker locker(& m_bMutex);
	BDataContainer::iterator it = m_bData.find(addr);
	Q_ASSERT_X(it != m_bData.end(), __func__, "coil has not been referenced yet");
	bool val = (*it)->requestedValue();
	qDebug() << "Writing requested value (" << val << ") to coil " << addr << ".";
	if (m_connection->writeB(addr, val) != 1)
		qWarning() << tr("Failed to write coil value to the device.");
	else
		emit (*it)->valueWritten();
}

void Client::connect()
{
	if (m_connection->connect())
		emit connected();
	else
		emit error(base::errorInfo(Error(Error::UNABLE_TO_CONNECT)));
}

void Client::disconnect()
{
	m_connection->disconnect();
	emit disconnected();
}

void Client::readAll(const QAtomicInt & run)
{
	readRegisters<IrDataContainer>(m_irData, & Client::readIr, run);
	readRegisters<RDataContainer>(m_rData, & Client::readR, run);
	readRegisters<IbDataContainer>(m_ibData, & Client::readIb, run);
	readRegisters<BDataContainer>(m_bData, & Client::readB, run);
}

void Client::rValueRequest(int index)
{
	QtConcurrent::run([](Client * me, int index) {me->writeR(index); me->readR(index);}, this, index);
}

void Client::bValueRequest(int index)
{
	QtConcurrent::run([](Client * me, int index) {me->writeB(index); me->readB(index);}, this, index);
}

HoldingRegister * Client::RAt(QQmlListProperty<HoldingRegister> * property, int index)
{
	// Can convert lambda to function pointer if lambda captures nothing according to standard
	// (via stackoverflow -> http://stackoverflow.com/questions/28746744/passing-lambda-as-function-pointer).
	// "The closure type for a lambda-expression with no lambda-capture has a public non-virtual non-explicit const conversion function
	//  to pointer to function having the same parameter and return types as the closure type’s function call operator. The value
	//  returned by this conversion function shall be the address of a function that, when invoked, has the same effect as invoking the
	//  closure type’s function call operator." -- draft C++11 standard section 5.1.2 [expr.prim.lambda]
	auto onCreate = [](QQmlListProperty<HoldingRegister> * property, int index, HoldingRegister * reg) {
		Client * client = static_cast<Client *>(property->object);
		QSignalMapper * mapper = client->m_rValueRequestMapper;
		mapper->setMapping(reg, index);
		QObject::connect(reg, SIGNAL(valueRequested()), mapper, SLOT(map()));
	};
	HoldingRegister * reg = At<HoldingRegister>(property, index, onCreate);

	return reg;
}

InputRegister * Client::IrAt(QQmlListProperty<InputRegister> * property, int index)
{
	InputRegister * reg = At<InputRegister>(property, index);
	return reg;
}

Coil * Client::BAt(QQmlListProperty<Coil> * property, int index)
{
	// Can convert lambda to function pointer if lambda captures nothing according to standard
	// (via stackoverflow -> http://stackoverflow.com/questions/28746744/passing-lambda-as-function-pointer).
	// "The closure type for a lambda-expression with no lambda-capture has a public non-virtual non-explicit const conversion function
	//  to pointer to function having the same parameter and return types as the closure type’s function call operator. The value
	//  returned by this conversion function shall be the address of a function that, when invoked, has the same effect as invoking the
	//  closure type’s function call operator." -- draft C++11 standard section 5.1.2 [expr.prim.lambda]
	auto onCreate = [](QQmlListProperty<Coil> * property, int index, Coil * reg) {
		Client * client = static_cast<Client *>(property->object);
		QSignalMapper * mapper = client->m_bValueRequestMapper;
		mapper->setMapping(reg, index);
		QObject::connect(reg, SIGNAL(valueRequested()), mapper, SLOT(map()));
	};
	Coil * reg = At<Coil>(property, index, onCreate);

	return reg;
}

DiscreteInput * Client::IbAt(QQmlListProperty<DiscreteInput> * property, int index)
{
	DiscreteInput * reg = At<DiscreteInput>(property, index);
	return reg;
}

uint16_t Client::fromClientEndian(uint16_t val) const
{
	switch (endianness()) {
		case ENDIAN_BIG:
			return fromBigEndian(val);
		case ENDIAN_LITTLE:
			return fromLittleEndian(val);
		default:
			qFatal("Unrecognized endiannes code: %d.", endianness());
	}
}

uint16_t Client::toClientEndian(uint16_t val) const
{
	switch (endianness()) {
		case ENDIAN_BIG:
			return toBigEndian(val);
		case ENDIAN_LITTLE:
			return toLittleEndian(val);
		default:
			qFatal("Unrecognized endiannes code: %d.", endianness());
	}
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
