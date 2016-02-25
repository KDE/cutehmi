#include "Client.hpp"
#include "AbstractConnection.hpp"
#include "Exception.hpp"
#include "functions.hpp"

#include <QtDebug>
#include <QMutexLocker>

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
	m_connection(std::move(connection)),
	m_endianness(INITIAL_ENDIANNESS),
	m_rValueRequestMapper(new QSignalMapper(this))
{
	QObject::connect(m_rValueRequestMapper, SIGNAL(mapped(int)), this, SLOT(valueRequest(int)));
}

Client::~Client()
{
	for (IrDataContainer::iterator it = m_irData.begin(); it != m_irData.end(); ++it)
		delete it.value();
	m_irData.clear();
	for (RDataContainer::iterator it = m_rData.begin(); it != m_rData.end(); ++it)
		delete it.value();
	m_rData.clear();
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

void Client::readIr(int addr)
{
	const int NUM_READ = 1;

	QMutexLocker locker(& m_irMutex);
	IrDataContainer::iterator it = m_irData.find(addr);
	Q_ASSERT_X(it != m_irData.end(), __func__, "register has not been referenced yet");
	uint16_t val;
	qDebug() << "Reading value from input register " << addr << ".";
	if (m_connection->readIr(addr, NUM_READ, val) != NUM_READ)
		qWarning() << tr("Failed reading input register value from a device.");
	else
		it.value()->updateValue(val); // libmodbus seems to take care about endianness, so fromClientEndian(val) is not necessary.
}

void Client::readR(int addr)
{
	static const int NUM_READ = 1;

	QMutexLocker locker(& m_rMutex);
	RDataContainer::iterator it = m_rData.find(addr);
	Q_ASSERT_X(it != m_rData.end(), __func__, "register has not been referenced yet");
	uint16_t val;
	qDebug() << "Reading value from holding register " << addr << ".";
	if (m_connection->readR(addr, NUM_READ, val) != NUM_READ)
		qWarning() << tr("Failed reading register value from a device.");
	else
		it.value()->updateValue(val); // libmodbus seems to take care about endianness, so fromClientEndian(val) is not necessary.
}

void Client::writeR(int addr)
{
	QMutexLocker locker(& m_rMutex);
	RDataContainer::iterator it = m_rData.find(addr);
	Q_ASSERT_X(it != m_rData.end(), __func__, "register has not been referenced yet");
	uint16_t val = it.value()->requestedValue();
	qDebug() << "Writing requested value (" << val << ") to holding register " << addr << ".";
	if (m_connection->writeR(addr, val) != 1)
		qWarning() << tr("Failed writing register value to a device.");
}

void Client::connect()
{
	m_connection->connect();
	if (m_connection->connected()) {
		qDebug("Modbus client connected to the device.");
		emit connected();
	} else
		emit error(base::errorInfo(Error(Error::UNABLE_TO_CONNECT)));
}

void Client::disconnect()
{
	if (m_connection->connected()) {
		m_connection->disconnect();
		qDebug("Modbus client disconnected from the device.");
		emit disconnected();
	} else
		qDebug("Already disconnected.");
}

void Client::readAll()
{
	if (!m_connection->connected()) {
		qDebug("Attempting to read while not connected.");
		return;
	}
	for (IrDataContainer::iterator it = m_irData.begin(); it != m_irData.end(); ++it)
		readIr(it.key());
	for (RDataContainer::iterator it = m_rData.begin(); it != m_rData.end(); ++it)
		readR(it.key());
}

void Client::valueRequest(int index)
{
	writeR(index);
	readR(index);
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
