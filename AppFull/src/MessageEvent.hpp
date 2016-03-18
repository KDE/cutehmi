#ifndef CUTEHMI_APPFULL_SRC_MESSAGEEVENT_HPP
#define CUTEHMI_APPFULL_SRC_MESSAGEEVENT_HPP

#include <QEvent>
#include <QString>

namespace cutehmi {

class MessageEvent:
	public QEvent
{
	public:
		const QString msg;	///< Message string.

		static int EventType();

		/**
		 * Contructor.
		 * 	@param msg message to post.
		 */
		MessageEvent(const QString & msg);
};

}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
