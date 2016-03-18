#include "MessageEvent.hpp"

namespace cutehmi {

int MessageEvent::EventType()
{
	static int Type = QEvent::registerEventType();
	return Type;
}

MessageEvent::MessageEvent(const QString & p_msg):
	QEvent(static_cast<QEvent::Type>(EventType())),
	msg(p_msg)
{
}

}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
