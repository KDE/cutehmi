#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_AUTH_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_AUTH_HPP

#include "internal/common.hpp"
#include "Client.hpp"

#include <QObject>
#include <QSettings>

namespace cutehmi {
namespace authssh {

class CUTEHMI_AUTHSSH_API Auth:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(bool authenticated READ authenticated NOTIFY authenticatedChanged)
		Q_PROPERTY(cutehmi::authssh::Client * client READ client CONSTANT)

		explicit Auth(QObject * parent = nullptr);

		bool authenticated() const;

		const Client * client() const;

		Client * client();

	public slots:
		bool login(const QString & user, const QString & password);

		void logout();

		void acceptHostKey();

	signals:
		void authenticatedChanged();

		void hostKeyNew();

		void hostKeyMismatch();

	protected:
		void setAuthenticated(bool authenticated);

	private:
		QString hostKeySettingsKey() const;

		struct Members
		{
			bool authenticated{false};
			Client client;
			QSettings settings;
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
