#include "RunnersRegister.hpp"
#include "IRunner.hpp"

namespace cutehmi {
namespace base {

void RunnersRegister::add(IRunner * runner)
{
	m_runners.append(runner);
}

void RunnersRegister::clear()
{
	m_runners.clear();
}

void RunnersRegister::start()
{
	for (IRunner * runner : m_runners)
		runner->start();
}

void RunnersRegister::stop()
{
	for (IRunner * runner : m_runners)
		runner->stop();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
