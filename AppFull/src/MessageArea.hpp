#ifndef CUTEHMI_APPFULL_SRC_MESSAGEAREA_HPP
#define CUTEHMI_APPFULL_SRC_MESSAGEAREA_HPP

#include <QTextEdit>

namespace cutehmi {

class MessageArea:
	public QTextEdit
{
	public:
//		/**
//		 * Append notice.
//		 * @param msg message.
//		 */
//		static void Append(const char * msg);

		MessageArea(QWidget * parent = 0);

		MessageArea(const QString & text, QWidget * parent = 0);

		~MessageArea() override = default;

		/**
		 * Post message event to the main event loop. This function encapsulates
		 * message into MessageEvent object and passes it to the main event loop.
		 * 	@param type message type.
		 * 	@param msg message string.
		 */
		void postMsgEvent(QtMsgType type, const QString & msg);

	protected:
		/**
		 * Handle custom events. MessageWindow hadles custom events listed in
		 * EventType enum.
		 */
		virtual void customEvent(QEvent * event);

//	private:
//		static MessageArea * MsgHandler;	///< Set in constructor.
};

}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
