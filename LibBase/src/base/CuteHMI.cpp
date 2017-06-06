#include "../include/base/CuteHMI.hpp"

namespace cutehmi {
namespace base {

CuteHMI & CuteHMI::Instance()
{
	return *(InstancePtr().get());
}

void CuteHMI::Destroy()
{
	InstancePtr().reset();
}

Project * CuteHMI::project() const
{
	return m->project.get();
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
	  std::unique_ptr<Project>(new Project),
	  std::unique_ptr<PopupBridge>(new PopupBridge),
	  std::unique_ptr<NotificationManager>(new NotificationManager)})
{
	qRegisterMetaType<cutehmi::base::ErrorInfo>();
	qRegisterMetaType<cutehmi::base::Prompt::button_t>();
}

std::unique_ptr<CuteHMI> & CuteHMI::InstancePtr()
{
	static std::unique_ptr<CuteHMI> instance(new CuteHMI);
	return instance;
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
