#include "../../include/cutehmi/CuteHMI.hpp"

namespace cutehmi {

CuteHMI & CuteHMI::Instance()
{
	//<CuteHMI-2.workaround>
	// Function std::unique_ptr::reset() sets internal pointer to nullptr and only after that it will
	// delete its contents. This causes error, when managed object still needs to be accessed through
	// std::unique_ptr::get() function by members of managed object during their destruction.
	// Workaround is to use additional raw pointer.
	static CuteHMI * instancePtr = InstancePtr().get();
	return *instancePtr;
	//</CuteHMI-2.workaround.2>
}

void CuteHMI::Destroy()
{
	//<CuteHMI-2.workaround>
	Instance();	// A bit paranoic, but if Instance() wasn't called before, it would point to nullptr.
	//</CuteHMI-2.workaround>
	InstancePtr().reset();
}

Dialogist * CuteHMI::dialogist() const
{
	return m->dialogist.get();
}

Notifier * CuteHMI::notifier() const
{
	return m->notifier.get();
}

CuteHMI::CuteHMI():
	m(new Members{
	  std::unique_ptr<Dialogist>(new Dialogist),
	  std::unique_ptr<Notifier>(new Notifier)})
{
	qRegisterMetaType<cutehmi::ErrorInfo>();
	qRegisterMetaType<cutehmi::Dialog::Button>();
}

std::unique_ptr<CuteHMI> & CuteHMI::InstancePtr()
{
	static std::unique_ptr<CuteHMI> instance(new CuteHMI);
	return instance;
}

}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
