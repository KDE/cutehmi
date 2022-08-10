#ifndef H_EXTENSIONS_CUTEHMI_LOCKSCREEN_2_INCLUDE_CUTEHMI_LOCKSCREEN_GATEKEEPER_HPP
#define H_EXTENSIONS_CUTEHMI_LOCKSCREEN_2_INCLUDE_CUTEHMI_LOCKSCREEN_GATEKEEPER_HPP

#include "internal/common.hpp"

#include <cutehmi/Singleton.hpp>

#include <QQmlEngine>

namespace cutehmi {
namespace lockscreen {

class CUTEHMI_LOCKSCREEN_API Gatekeeper:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(Gatekeeper)

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

//(c)C: Copyright © 2021-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
