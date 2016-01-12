#ifndef CUTEHMI_LIBBASE_SRC_BASE_PLCCLIENTMANAGER_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_PLCCLIENTMANAGER_HPP

#include "../modbus/Client.hpp"
//#include "modbus/ClientControlWidget.hpp"
#include "../modbus/ClientPlugin.hpp"	/// @todo remove from here if real plugin
#include "../utils/Singleton.hpp"

namespace base {

/**
 * Programable logic controler client manager.
 */
class CUTEHMI_API PLCClientManager:
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
