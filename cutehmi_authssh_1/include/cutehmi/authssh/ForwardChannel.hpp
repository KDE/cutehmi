#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_FORWARDCHANNEL_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_FORWARDCHANNEL_HPP

#include "internal/common.hpp"
#include "internal/ChannelsThread.hpp"
#include "internal/TunnelEntrance.hpp"
#include "AbstractChannel.hpp"

#include <libssh/libssh.h>

#include <QSocketNotifier>
#include <QByteArray>

namespace cutehmi {
namespace authssh {

class CUTEHMI_AUTHSSH_API ForwardChannel:
	public AbstractChannel
{
	public:
		ForwardChannel(const QHostAddress & remoteHost, uint remotePort, const QHostAddress & sourceHost, uint localPort);

		~ForwardChannel() override;

	protected:
		bool initChannel(ssh_channel channel) override;

		bool processChannel(ssh_channel channel) override;

		void shutdownChannel(ssh_channel channel) override;

	private:
		void shutdown();

		struct Members
		{
			QByteArray remoteHost;	// Using 'QByteArray' internally instead of 'QHostAddress', because 'libssh' requires valid 'const char *' pointer.
			uint remotePort;
			QByteArray sourceHost;
			uint localPort;
			// workaround libssh limitted threads - need to use unique_ptr to allocate in proper thread, need to use QSocketNotifier
			std::unique_ptr<internal::TunnelEntrance> tunnelEntrance;	// Will be allocated in appropriate thread within 'initChannel()'.
			std::unique_ptr<QSocketNotifier> sessionReadNotifier;
			QByteArray channelBuffer;
			// /workaround

			Members(const QByteArray & p_remoteHost, uint p_remotePort, const QByteArray & p_sourceHost, uint p_localPort):
				remoteHost(p_remoteHost),
				remotePort(p_remotePort),
				sourceHost(p_sourceHost),
				localPort(p_localPort)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // FORWARDCHANNEL_HPP
