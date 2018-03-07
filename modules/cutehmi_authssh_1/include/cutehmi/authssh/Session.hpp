#ifndef H_MODULES_CUTEHMI__AUTHSSH__1_INCLUDE_CUTEHMI_AUTHSSH_SESSION_HPP
#define H_MODULES_CUTEHMI__AUTHSSH__1_INCLUDE_CUTEHMI_AUTHSSH_SESSION_HPP

#include "internal/common.hpp"

#include <cutehmi/Error.hpp>

#include <libssh/libssh.h>

#include <QObject>
#include <QMutex>
#include <QList>

namespace cutehmi {
namespace authssh {

namespace internal { class ChannelsThread; }

class CUTEHMI_AUTHSSH_API Session:
	public QObject
{
	Q_OBJECT

	friend class internal::ChannelsThread;

	public:
		struct CUTEHMI_AUTHSSH_API Error:
			public cutehmi::Error
		{
			enum : int {
				FAILED_GET_PUBLIC_KEY = Error::SUBCLASS_BEGIN,
				FAILED_GET_PUBLIC_KEY_HASH,
				FAILED_PUBLIC_KEY_HEX_STRING,
				ALREADY_CONNNECTED,
				COULD_NOT_CONNECT
			};

			using cutehmi::Error::Error;

			QString str() const;
		};

		explicit Session(const QString & host, uint port, const QString & user, QObject * parent = nullptr) noexcept(false);

		~Session() override;

		QString host() const;

		uint port() const;

		QString user() const;

		bool connected() const;

		std::pair<Error, QString> getServerKey();

		Error connect();

		void disconnect();

		bool passwordAuth(const QString & password);

	protected:
		ssh_session session() const;

		//<workaround ref="cutehmi_authssh_1-1" target="libssh" cause="bug">
		void setConnected(bool connected);
		//</workaround>

	private:
#ifdef CUTEHMI_DEBUG
		static const int INITIAL_LIBSSH_VERBOSITY = SSH_LOG_FUNCTIONS;
#else
		static const int INITIAL_LIBSSH_VERBOSITY = SSH_LOG_NOLOG;
#endif

		ssh_session acquireLibsshSession();

		void releaseLibsshSession(ssh_session session);

		QStringList authMethods() const;

	private:
		struct Members
		{
			QString host;
			uint port;
			QString user;
			QString serverKeyCache;
			ssh_session session;
			//<workaround id="cutehmi_authssh_1-1" target="libssh" cause="bug">
			// Function 'ssh_is_connected()' returns true, even if 'ssh_connect()' fails to establish connection due to	timeout.
			bool connected;
			//</workaround>

			Members(const QString & p_host, uint p_port, const QString & p_user):
				host(p_host),
				port(p_port),
				user(p_user),
				session(NULL),
				connected(false)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
