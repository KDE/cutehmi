#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_NODEDATAOBJECT_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_NODEDATAOBJECT_HPP

#include "Client.hpp"
#include "ClientRunner.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API NodeDataObject:
	public QObject
{
	Q_OBJECT

	public:
		NodeDataObject(std::unique_ptr<Client> client, std::unique_ptr<ClientRunner> clientRunner, QObject * parent = nullptr);

		~NodeDataObject() override = default;

		Client * client() const;

		ClientRunner * clientRunner() const;

	private:
		std::unique_ptr<Client> m_client;
		std::unique_ptr<ClientRunner> m_clientRunner;
};

}
}

#endif
