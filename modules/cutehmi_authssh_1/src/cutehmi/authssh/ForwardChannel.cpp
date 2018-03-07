#include "../../../include/cutehmi/authssh/ForwardChannel.hpp"
#include "../../../include/cutehmi/authssh/Exception.hpp"

#include <cutehmi/Worker.hpp>

namespace cutehmi {
namespace authssh {

ForwardChannel::ForwardChannel(const QHostAddress & remoteHost, uint remotePort, const QHostAddress & sourceHost, uint localPort):
	m(new Members(remoteHost.toString().toLocal8Bit(), remotePort, sourceHost.toString().toLocal8Bit(), localPort))
{
}

ForwardChannel::~ForwardChannel()
{
	if (isInitialized())
		shutdown();
}

bool ForwardChannel::initChannel(ssh_channel channel)
{
	CUTEHMI_ASSERT(channel != NULL, "channel must not be NULL");

	std::unique_ptr<QSocketNotifier> sessionReadNotifier(new QSocketNotifier(ssh_get_fd(ssh_channel_get_session(channel)), QSocketNotifier::Read));
	connect(sessionReadNotifier.get(), & QSocketNotifier::activated, this, & AbstractChannel::activated);

	CUTEHMI_LOG_DEBUG("Opening forward channel.");
	int errorCode;
	do
		errorCode = ssh_channel_open_forward(channel, m->remoteHost.constData(), m->remotePort, m->sourceHost.constData(), m->localPort);
	while (errorCode == SSH_AGAIN);

	if (errorCode != SSH_OK) {
		CUTEHMI_LOG_WARNING("Function 'ssh_channel_open_forward()' has failed (error code: " << errorCode << ").");
		emit error(QObject::tr("Could not open forward channel. Check if host '%1' is accepting connections on port '%2' or if it is not blocked by a firewall.")
						.arg(m->remoteHost.constData())
						.arg(m->remotePort));
		return false;
	}

	//<workaround id="cutehmi_authssh_lib_1-2" target="libssh" cause="bug">
	// Function 'ssh_channel_open_forward()' returns 'SSH_OK', even if it fails to open channel.
	if (!ssh_channel_is_open(channel)) {
		CUTEHMI_LOG_WARNING("Function 'ssh_channel_open_forward()' has failed to open channel.");
		emit error(QObject::tr("Could not open forward channel. Check if host '%1' is accepting connections on port '%2' or if it is not blocked by a firewall.")
						.arg(m->remoteHost.constData())
						.arg(m->remotePort));
		return false;
	}
	//</workaround>

	m->sessionReadNotifier = std::move(sessionReadNotifier);

	m->tunnelEntrance.reset(new internal::TunnelEntrance(QHostAddress(QString::fromLocal8Bit(m->sourceHost)), m->localPort));
	connect(m->tunnelEntrance.get(), & internal::TunnelEntrance::readyRead, this, & AbstractChannel::activated);
	m->tunnelEntrance->open();

	return true;
}

bool ForwardChannel::processChannel(ssh_channel channel)
{
	CUTEHMI_LOG_DEBUG("Processing forward channel.");

	int available = m->tunnelEntrance->bytesAvailable();
	if (available > 0) {
		m->channelBuffer.clear();
		m->tunnelEntrance->read(m->channelBuffer);
		int written = 0;
		int n;
		do {
			n = ssh_channel_write(channel, m->channelBuffer.constData() + written, available - written);
			written += n;
		} while ((written != available) && (n != 0));
		if (written != available) {
			emit error(QObject::tr("Could not write data to the channel."));
			return false;
		}
	}

	available = ssh_channel_poll(channel, 0);
	if (available > 0) {
		m->channelBuffer.resize(available);
		int n = ssh_channel_read_nonblocking(channel, m->channelBuffer.data(), available, 0);
		if (n != available) {
			emit error(QObject::tr("Could not read data from channel."));
			return false;
		}
		int written;
		do {
			written = m->tunnelEntrance->write(m->channelBuffer);
			if (written != available) {
				m->channelBuffer.remove(0, written);
				available -= written;
			} else
				available = 0;
		} while (available && (written != 0));
		if (available != 0) {
			emit error(QObject::tr("Could not write data to the tunnel."));
			return false;
		}
	}
	return true;
}

void ForwardChannel::shutdownChannel(ssh_channel channel)
{
	CUTEHMI_LOG_DEBUG("Shutting down forward channel.");

	shutdown();

	ssh_channel_close(channel);
}

void ForwardChannel::shutdown()
{
	m->tunnelEntrance.release()->deleteLater();
	m->sessionReadNotifier.release()->deleteLater();
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
