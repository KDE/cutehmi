#ifndef CUTEHMI_LIBMODBUS_SRC_BASE_PLCCLIENTMANAGER_HPP
#define CUTEHMI_LIBMODBUS_SRC_BASE_PLCCLIENTMANAGER_HPP

#include "../modbus/Client.hpp"
//#include "modbus/ClientControlWidget.hpp"
#include "../modbus/ClientPlugin.hpp"
#include "../platform.hpp"

#include <utils/Singleton.hpp>

namespace base {

/**
 * Programable logic controler client manager.
 *
 * @deprecated this is temporary here unless plugin interface is implemented.
 */
class CUTEHMI_MODBUS_API PLCClientManager:
	public utils::Singleton<PLCClientManager>
{
	friend class utils::Singleton<PLCClientManager>;

	private:
		/**
		 * Default constructor. This class is a singleton and can't be instantiated directly.
		 */
		PLCClientManager();

		/**
		 * Destructor. This class is a singleton and can't be instantiated directly.
		 */
		~PLCClientManager() override = default;

	/** @todo temporary public access, until AbstractPLCClient is implemented, management is based on a model and appropriate methods are provided. */
	public:
		//fake plugin for now
		modbus::ClientPlugin m_modbusClientPlugin;
		//for now manager "manages" following
		modbus::Client * m_modbusClient;
};

}

#endif
