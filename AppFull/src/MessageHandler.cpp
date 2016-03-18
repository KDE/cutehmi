#include "MessageHandler.hpp"
#include "MessageArea.hpp"

#include <QMutexLocker>

#include <iostream>

namespace cutehmi {

void MessageHandler::qtMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg)
{
	Q_UNUSED(context);

	static QMutex mutex;
	QMutexLocker locker(&mutex);

	if (messageArea() != nullptr)
		return messageArea()->postMsgEvent(type, msg);
	else
		std::cerr << MessageHandler::QtMsgToString(type, msg).toLocal8Bit().constData() << "\n";
}

void MessageHandler::setMessageArea(MessageArea * messageArea)
{
	m_messageArea = messageArea;
}

MessageArea * MessageHandler::messageArea() const
{
	return m_messageArea;
}

QString MessageHandler::QtMsgToString(QtMsgType type, const QString & msg)
{
	switch (type) {
		case QtDebugMsg:
			return QObject::tr("Debug: %1").arg(msg);
		case QtWarningMsg:
			return QObject::tr("Warning: %1").arg(msg);
		case QtCriticalMsg:
			return QObject::tr("Critical error: %1").arg(msg);
		case QtFatalMsg:
			return QObject::tr("Fatal error: %1").arg(msg);
		default:
			return QObject::tr("Unrecognized message type: %1").arg(msg);
	}
}

MessageHandler::MessageHandler():
	m_messageArea(nullptr)
{
}

}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
