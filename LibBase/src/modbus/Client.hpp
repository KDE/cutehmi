#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_CLIENT_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_CLIENT_HPP

#include "RegisterTraits.hpp"

#include <QObject>
#include <QQmlListProperty>
#include <QHash>

#include <memory>

namespace modbus {

class AbstractConnection;

/**
 * Modbus client.
 */
class CUTEHMI_API Client:
	public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<modbus::InputRegister> ir READ ir NOTIFY irChanged)
	Q_PROPERTY(QQmlListProperty<modbus::HoldingRegister> r READ r NOTIFY rChanged)
//remember to delete container elements!!!
//	Q_PROPERTY(QQmlListProperty<modbus::ModbusDiscreteInput> ib READ ib NOTIFY ibChanged)
//	Q_PROPERTY(QQmlListProperty<modbus::ModbusCoil> b READ b NOTIFY bChanged)
//32 bit registers/16 bit addressing	(alternatively idr/dr (double register, then could be qr - quad for 64 bit)
//	Q_PROPERTY(QQmlListProperty<modbus::InputRegister> irr READ irr NOTIFY irChanged)
//	Q_PROPERTY(QQmlListProperty<modbus::HoldingRegister> rr READ rr NOTIFY rChanged)

	public:
		template <typename T>
		static T * At(QQmlListProperty<T> * property, int index);

		template <typename T>
		static int Count(QQmlListProperty<T> * property);

		Client(std::unique_ptr<AbstractConnection> connection, QObject * parent = 0);

		~Client() override;

		const QQmlListProperty<InputRegister> & ir() const;

		const QQmlListProperty<HoldingRegister> & r() const;

//		void setConnection(std::unique_ptr<AbstractConnection> connection);

	public slots:
		void connect();

		void disconnect();

	signals:
		void error(const QString & message, const QString & details = QString());

		void connected();

		void disconnected();

		void irChanged();

		void rChanged();

		void ibChanged();

		void bChanged();

	private:
		typedef typename RegisterTraits<InputRegister>::Container IrDataContainer; ///< Holds (address, register) pairs. @note Qt uses int type for sizes and indices.
		typedef typename RegisterTraits<HoldingRegister>::Container RDataContainer; ///< Holds (address, register) pairs. @note Qt uses int type for sizes and indices.

		IrDataContainer m_irData;
		QQmlListProperty<InputRegister> m_ir;
		RDataContainer m_rData;
		QQmlListProperty<HoldingRegister> m_r;
		std::unique_ptr<AbstractConnection> m_connection;
};

template <typename T>
T * Client::At(QQmlListProperty<T> * property, int index)
{
	typedef typename RegisterTraits<T>::Container Container;
	Container * propertyData = static_cast<Container *>(property->data);
	typename Container::iterator it = propertyData->find(index);
	if (it == propertyData->end())
		it = propertyData->insert(index, new T);
	return it.value();
}

template <typename T>
int Client::Count(QQmlListProperty<T> * property)
{
	Q_UNUSED(property);

	return std::numeric_limits<int>::max();
}

}

#endif
