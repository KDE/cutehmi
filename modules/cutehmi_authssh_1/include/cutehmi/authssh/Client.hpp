#ifndef H_MODULES_CUTEHMI_u_AUTHSSH_u_1_INCLUDE_CUTEHMI_AUTHSSH_CLIENT_HPP
#define H_MODULES_CUTEHMI_u_AUTHSSH_u_1_INCLUDE_CUTEHMI_AUTHSSH_CLIENT_HPP

#include "internal/common.hpp"
#include "internal/ChannelsThread.hpp"
#include "Session.hpp"

#include <QObject>
#include <QSettings>
#include <QVariantList>

namespace cutehmi {
namespace authssh {

/**
 * @todo create Init() function add add libssh thread initialization code there.
 */
class CUTEHMI_AUTHSSH_API Client:
	public QObject
{
	Q_OBJECT

	public:
		static constexpr const char * QSETTINGS_GROUP = "cutehmi_authssh_1";
		static constexpr const char * INITIAL_SERVER_HOST = "localhost";
		static constexpr uint INITIAL_SERVER_PORT = 22;

		Q_PROPERTY(QString serverHost READ serverHost WRITE setServerHost NOTIFY serverHostChanged)
		Q_PROPERTY(uint serverPort READ serverPort WRITE setServerPort NOTIFY serverPortChanged)
		Q_PROPERTY(QString serverKey READ serverKey NOTIFY serverKeyChanged)
		Q_PROPERTY(QString user READ user NOTIFY userChanged)
		Q_PROPERTY(bool authenticated READ authenticated NOTIFY authenticatedChanged)

		explicit Client(QObject * parent = nullptr);

		~Client() override;

		QString serverHost() const;

		void setServerHost(const QString & host);

		uint serverPort() const;

		void setServerPort(uint port);

		QString serverKey() const;

		QString user() const;

		bool authenticated() const;

		void addChannel(std::unique_ptr<AbstractChannel> channel);

//		const Session * client() const;

//		Session * client();

	public slots:
		void acceptServerKey();

		void invalidateServerKey();

		bool login(const QString & user, const QString & password);

		void logout();

	signals:
		void serverHostChanged();

		void serverPortChanged();

		void serverKeyChanged();

		void userChanged();

		void authenticatedChanged();

		void serverKeyNew();

		void serverKeyMismatch();

	protected:
		void setServerKey(const QString & key);

		void setUser(const QString & user);

		void setAuthenticated(bool authenticated);

		void startChannels(Session * session);

		void stopChannels();

	private slots:
		void handleChannelError(const QString & error);

	private:
		typedef QVariantList SessionCointainer;

		Session * lastSession();

		const Session * lastSession() const;

		Session * takeLastSession();

//		bool connect();

		bool verifyServer();

//		void disconnect();

		QString serverKeySettingsKey() const;

		struct Members
		{
			QString serverHost{Client::INITIAL_SERVER_HOST};
			uint serverPort{Client::INITIAL_SERVER_PORT};
			QString serverKey;
			QString user;
			bool authenticated{false};
			Client::SessionCointainer sessions;
			QSettings settings;
			//<workaround id="cutehmi_authssh_1-3" target="libssh" cause="design">
			// "You cannot use a single session (or channels for a single session) in several threads at the same time. This will most likely lead to internal state corruption. This limitation is being worked out and will maybe disappear later." -- http://api.libssh.org/master/libssh_tutor_threads.html
			// Workaround is to use collective thread for all channels.
			internal::ChannelsThread channelsThread;
			//</workaround>
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
