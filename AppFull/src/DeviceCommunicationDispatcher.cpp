#include "DeviceCommunicationDispatcher.hpp"
#include "DevicePoint.hpp"

void DeviceCommunicationDispatcher::registerPoint(DevicePoint * device)
{
	m_devices.append(device);
}

void DeviceCommunicationDispatcher::deregisterPoint(DevicePoint * device)
{
	m_devices.removeOne(device);
}
