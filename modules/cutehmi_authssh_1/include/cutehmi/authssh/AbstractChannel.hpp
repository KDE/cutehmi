#ifndef H_MODULES_CUTEHMI__AUTHSSH__1_INCLUDE_CUTEHMI_AUTHSSH_ABSTRACTCHANNEL_HPP
#define H_MODULES_CUTEHMI__AUTHSSH__1_INCLUDE_CUTEHMI_AUTHSSH_ABSTRACTCHANNEL_HPP

#include "internal/common.hpp"
#include "Exception.hpp"

#include <QObject>
#include <QMap>

#include <libssh/libssh.h>

namespace cutehmi {
namespace authssh {

class CUTEHMI_AUTHSSH_API AbstractChannel:
	public QObject
{
	Q_OBJECT

	public:
		virtual ~AbstractChannel();

		bool isInitialized() const;

		bool init(ssh_session session);

//		bool switchSession(ssh_session session);

		void shutdown();

	signals:
		void initialized();

		void activated();

		/**
		 * Channel closed. Indicates that channel has been closed. This signal is emitted after
		 * channel has been shut down by shutdown() function.
		 */
		void closed();

		void error(const QString & message);

	protected:
		AbstractChannel();

		virtual bool initChannel(ssh_channel channel) = 0;

		/**
		 * Process channel. This function is called whenever activated() signal is emitted.
		 * It is up to subclasses to emit activated() signal, when they find it appropriate.
		 * @param channel channel handle.
		 *
		 * @warning implementation must be non-blocking, because all channels are processed in
		 * a collective thread.
		 */
		virtual bool processChannel(ssh_channel channel) = 0;

		virtual void shutdownChannel(ssh_channel channel) = 0;

	private slots:
		void process();

	private:
//		typedef QMap<ssh_session, ssh_channel> SessionChannelContainer;

		void freeChannel();

		struct Members
		{
			ssh_channel channel;
//			SessionChannelContainer sessionChannels;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
