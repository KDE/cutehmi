#include "../../include/cutehmi/CuteHMI.hpp"

namespace cutehmi {

CuteHMI & CuteHMI::Instance()
{
	//<workaround id="cutehmi_1-2" target="std" cause="design">
	// Function std::unique_ptr::reset() sets internal pointer to nullptr and only after that it will
	// delete its contents. This causes error, when managed object still needs to be accessed through
	// std::unique_ptr::get() function by members of managed object during their destruction.
	// Workaround is to use additional raw pointer.
	static CuteHMI * instancePtr = InstancePtr().get();
	return *instancePtr;
	//</workaround>
}

void CuteHMI::Destroy()
{
	//<workaround ref="cutehmi_1-2">
	Instance();	// A bit paranoic, but if Instance() wasn't called before, it would point to nullptr.
	//</workaround>
	InstancePtr().reset();
}

PopupBridge * CuteHMI::popupBridge() const
{
	return m->popupBridge.get();
}

NotificationManager * CuteHMI::notificationManager() const
{
	return m->notificationManager.get();
}

CuteHMI::CuteHMI():
	m(new Members{
	  std::unique_ptr<PopupBridge>(new PopupBridge),
	  std::unique_ptr<NotificationManager>(new NotificationManager)})
{
	qRegisterMetaType<cutehmi::ErrorInfo>();
	qRegisterMetaType<cutehmi::Prompt::Button>();
}

std::unique_ptr<CuteHMI> & CuteHMI::InstancePtr()
{
	static std::unique_ptr<CuteHMI> instance(new CuteHMI);
	return instance;
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
