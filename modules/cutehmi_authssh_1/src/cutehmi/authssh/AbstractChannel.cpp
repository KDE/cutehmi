#include "../../../include/cutehmi/authssh/AbstractChannel.hpp"
#include "../../../include/cutehmi/authssh/Exception.hpp"

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
	CUTEHMI_ASSERT(session != NULL, "session must not be NULL");

	m->channel = ssh_channel_new(session);
	if (m->channel == NULL) {
		CUTEHMI_LOG_WARNING("Function 'ssh_channel_new()' returned NULL.");
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
//	CUTEHMI_ASSERT(session != NULL, "session must not be NULL");

//	m->channel = ssh_channel_new(session);
//	if (m->channel == NULL) {
//		CUTEHMI_LOG_WARNING("Function 'ssh_channel_new()' returned NULL.");
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
	CUTEHMI_ASSERT(m->channel != NULL, "channel must not be NULL (forget to initialize?)");

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
	CUTEHMI_ASSERT(m->channel != NULL, "channel must not be NULL (forget to initialize?)");

	if (!processChannel(m->channel)) {
		CUTEHMI_LOG_WARNING("Shutting down channel due to processing error.");
		shutdown();
	}
}

void AbstractChannel::freeChannel()
{
	CUTEHMI_ASSERT(m->channel != NULL, "channel already freed");

	ssh_channel_free(m->channel);
	m->channel = NULL;
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
