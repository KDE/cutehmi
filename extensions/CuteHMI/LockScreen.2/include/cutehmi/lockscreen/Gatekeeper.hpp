#ifndef H_EXTENSIONS_CUTEHMI_LOCKSCREEN_2_INCLUDE_CUTEHMI_LOCKSCREEN_GATEKEEPER_HPP
#define H_EXTENSIONS_CUTEHMI_LOCKSCREEN_2_INCLUDE_CUTEHMI_LOCKSCREEN_GATEKEEPER_HPP

#include "internal/common.hpp"

#include <cutehmi/Singleton.hpp>

namespace cutehmi {
namespace lockscreen {

class CUTEHMI_LOCKSCREEN_API Gatekeeper:
	public QObject
{
		Q_OBJECT

		friend class test_Gatekeeper;

	public:
		static constexpr int INITIAL_HASHES_MIN = 9000;
		static constexpr int INITIAL_HASHES_MAX = 10000;

		Q_PROPERTY(int hashesLow READ hashesLow WRITE setHashesLow NOTIFY hashesLowChanged)

		Q_PROPERTY(int hashesHigh READ hashesHigh WRITE setHashesHigh NOTIFY hashesHighChanged)

		Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

		Q_PROPERTY(QByteArray secret READ secret WRITE setSecret NOTIFY secretChanged)

		explicit Gatekeeper(QObject * parent = nullptr);

		int hashesLow() const;

		void setHashesLow(int low);

		int hashesHigh() const;

		void setHashesHigh(int high);

		QString password() const;

		void setPassword(const QString & password);

		QByteArray secret() const;

		void setSecret(const QByteArray & secret);

		Q_INVOKABLE virtual bool authenticate() const;

		Q_INVOKABLE virtual QByteArray makeSecret(const QString & password);

	signals:
		void hashesLowChanged();

		void hashesHighChanged();

		void passwordChanged();

		void secretChanged();

	protected:
		static QByteArray Hash(const QString & string);

		int pickNumberOfHashes() const;

	private:
		struct Members {
			int hashesMin;
			int hashesMax;
			QString password;
			QByteArray secret;
		};
		MPtr<Members> m;
};

}
}

#endif

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
