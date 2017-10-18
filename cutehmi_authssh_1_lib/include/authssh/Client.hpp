#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_CLIENT_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_CLIENT_HPP

#include "internal/common.hpp"

#include <base/Error.hpp>

#include <libssh/libssh.h>

#include <QObject>

namespace cutehmi {
namespace authssh {

class CUTEHMI_AUTHSSH_API Client:
	public QObject
{
	Q_OBJECT

	public:
		struct CUTEHMI_AUTHSSH_API Error:
			public base::Error
		{
			enum : int {
				FAILED_GET_PUBLIC_KEY = base::Error::SUBCLASS_BEGIN,
				FAILED_GET_PUBLIC_KEY_HASH,
				FAILED_PUBLIC_KEY_HEX_STRING
			};

			using base::Error::Error;

			QString str() const;
		};

		static constexpr const char * INITIAL_HOST = "localhost";
		static constexpr int INITIAL_PORT = 22;
		static constexpr const char * INITIAL_USER = "";
#ifdef CUTEHMI_DEBUG
		static const int INITIAL_VERBOSITY = SSH_LOG_FUNCTIONS;
#else
		static const int INITIAL_VERBOSITY = SSH_LOG_NOLOG;
#endif

		Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
		Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
		Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)
		//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
		// Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged STORED false)
		Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
		//</workaround>
		Q_PROPERTY(QString hostKey READ hostKey NOTIFY hostKeyChanged)

		explicit Client(QObject * parent = nullptr);

		~Client() override;

		QString host() const;

		void setHost(const QString & host);

		int port() const;

		void setPort(int port);

		QString user() const;

		void setUser(const QString & user);

		bool connected() const;

		QString hostKey() const;

		void newSession();

		void destroySession();

		bool hasSession() const;

		void connect();

		void disconnect();

		bool passwordAuth(const QString & password);

//		Q_INVOKABLE bool authPassword(const QString & password);

	signals:
		void hostChanged();

		void portChanged();

		void userChanged();

		void connectedChanged();

		void hostKeyChanged();

	protected:
		ssh_session session() const;

		Error updateHostKey();

		void setHostKey(const QString & key);

		//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
		void setConnected(bool connected);
		//</workaround>

	private:
		QStringList authMethods() const;

	private:
		struct Members
		{
			QString host;
			int port;
			QString user;
			QString hostKey;
			ssh_session session;
			//<workaround id="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
			// Function 'ssh_is_connected()' returns true, even if 'ssh_connect()' fails to establish connection due to	timeout.
			bool connected;
			//</workaround>
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
