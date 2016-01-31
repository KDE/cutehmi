#ifndef CUTEHMI_APPFULL_SRC_MESSAGEHANDLER_HPP
#define CUTEHMI_APPFULL_SRC_MESSAGEHANDLER_HPP

#include <utils/Singleton.hpp>

#include <QtGlobal>

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

#endif
