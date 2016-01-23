#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_CLIENTPLUGIN_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_CLIENTPLUGIN_HPP

#include "../platform.hpp"

class QWidget;
class Client;

namespace modbus {

/**
 * Modbus client plugin. This is a draft of plugin for the future versions.
 *
 * @internal PLCClientManager will load this and call initialize() method as a part of
 * PLCClientPlugin interface.
 */
class CUTEHMI_MODBUS_API ClientPlugin
{
	public:
		ClientPlugin();

		/**
		 * Create client.
		 * @return client.
		 *
		 * @note caller is responsible for deleting created object.
		 */
		Client * createClient() const;

		/**
		 * Create client control widget.
		 * @return client control widget.
		 *
		 * @note caller is responsible for deleting created object.
		 */
		QWidget * createControlWidget() const;
};

}

#endif
