#ifndef CUTEHMI_APPFULL_SRC_MESSAGEHANDLER_HPP
#define CUTEHMI_APPFULL_SRC_MESSAGEHANDLER_HPP

#include <utils/Singleton.hpp>

#include <QtGlobal>

namespace cutehmi {

class MessageArea;

class MessageHandler:
	public utils::Singleton<MessageHandler>
{
	friend class utils::Singleton<MessageHandler>;

	public:
		void qtMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg);

		void setMessageArea(MessageArea * messageArea);

		MessageArea * messageArea() const;

	private:
		static QString QtMsgToString(QtMsgType type, const QString & msg);

		MessageHandler();

		~MessageHandler() override = default;

		MessageArea * m_messageArea;
};

}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
