#ifndef CUTEHMI_APPFULL_SRC_MESSAGEEVENT_HPP
#define CUTEHMI_APPFULL_SRC_MESSAGEEVENT_HPP

#include <QEvent>
#include <QString>

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

#endif
