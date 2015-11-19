#ifndef CUTEHMI_APPFULL_SRC_DEVICECOMMUNICATIONDISPATCHER_HPP
#define CUTEHMI_APPFULL_SRC_DEVICECOMMUNICATIONDISPATCHER_HPP

#include "utils/Singleton.hpp"

#include <QList>

class DevicePoint;

class DeviceCommunicationDispatcher : public utils::Singleton<DeviceCommunicationDispatcher>
{
	friend class utils::Singleton<DeviceCommunicationDispatcher>;

	public:
		void registerPoint(DevicePoint * device);

		void deregisterPoint(DevicePoint * device);

//		void poll();

	private:
		typedef QList<DevicePoint *> DevicesContainer;

		/**
		 * Default constructor.
		 */
		DeviceCommunicationDispatcher() = default;

		~DeviceCommunicationDispatcher() override = default;

		DevicesContainer m_devices;

};

#endif
