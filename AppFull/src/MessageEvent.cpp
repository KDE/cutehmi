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
