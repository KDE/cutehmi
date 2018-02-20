#include "../../include/authssh/AbstractChannel.hpp"
#include "../../include/authssh/Exception.hpp"

namespace cutehmi {
namespace authssh {

AbstractChannel::~AbstractChannel()
{
	if (isInitialized())
		freeChannel();
}

bool AbstractChannel::isInitialized() const
{
	return m->channel != NULL;
}

bool AbstractChannel::init(ssh_session session)
{
	CUTEHMI_UTILS_ASSERT(session != NULL, "session must not be NULL");

	m->channel = ssh_channel_new(session);
	if (m->channel == NULL) {
		CUTEHMI_UTILS_WARNING("Function 'ssh_channel_new()' returned NULL.");
		emit error(QObject::tr("Could not create a channel."));
		return false;
	}

	if (initChannel(m->channel)) {
		emit initialized();
		return true;
	} else
		return false;
}

//bool AbstractChannel::switchSession(ssh_session session)
//{
//	CUTEHMI_UTILS_ASSERT(session != NULL, "session must not be NULL");

//	m->channel = ssh_channel_new(session);
//	if (m->channel == NULL) {
//		CUTEHMI_UTILS_WARNING("Function 'ssh_channel_new()' returned NULL.");
//		emit error(QObject::tr("Could not create a channel."));
//		return false;
//	}

////	if (switchChannel(m->channel)) {
////		emit sessionSwitched();
////		return true;
////	} else
////		return false;
//}

void AbstractChannel::shutdown()
{
	CUTEHMI_UTILS_ASSERT(m->channel != NULL, "channel must not be NULL (forget to initialize?)");

	shutdownChannel(m->channel);
	freeChannel();
	emit closed();
}

AbstractChannel::AbstractChannel():
	m(new Members{NULL})
{
	connect(this, & AbstractChannel::activated, this, & AbstractChannel::process);
}

void AbstractChannel::process()
{
	CUTEHMI_UTILS_ASSERT(m->channel != NULL, "channel must not be NULL (forget to initialize?)");

	if (!processChannel(m->channel)) {
		CUTEHMI_UTILS_WARNING("Shutting down channel due to processing error.");
		shutdown();
	}
}

void AbstractChannel::freeChannel()
{
	CUTEHMI_UTILS_ASSERT(m->channel != NULL, "channel already freed");

	ssh_channel_free(m->channel);
	m->channel = NULL;
}

}
}
