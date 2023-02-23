#include "Gatekeeper.hpp"

#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>
#include <QCryptographicHash>

namespace cutehmi {
namespace lockscreen {

constexpr int Gatekeeper::INITIAL_HASHES_MIN;
constexpr int Gatekeeper::INITIAL_HASHES_MAX;

Gatekeeper::Gatekeeper(QObject * parent):
	QObject(parent),
	m(new Members{
	INITIAL_HASHES_MIN,
	INITIAL_HASHES_MAX,
	"",
	""})
{
}

int Gatekeeper::hashesLow() const
{
	return m->hashesMin;
}

void Gatekeeper::setHashesLow(int low)
{
	if (low < 1) {
		CUTEHMI_WARNING("Can not set 'hashesLow' to a value lower than 1 (" << low << " given).");
		low = 1;
	}

	if (low != m->hashesMin) {
		m->hashesMin = low;
		emit hashesLowChanged();
	}
}

int Gatekeeper::hashesHigh() const
{
	return m->hashesMax;
}

void Gatekeeper::setHashesHigh(int high)
{
	if (high < hashesLow()) {
		CUTEHMI_WARNING("Can not set 'hashesHigh' to a value lower than 'hashesLow', which is " << hashesLow() << " (" << high << " given).");
		high = hashesLow();
	}

	if (high != m->hashesMax) {
		m->hashesMax = high;
		emit hashesHighChanged();
	}
}

QString Gatekeeper::password() const
{
	return m->password;
}

void Gatekeeper::setPassword(const QString & password)
{
	if (m->password != password) {
		m->password = password;
		emit passwordChanged();
	}
}

QByteArray Gatekeeper::secret() const
{
	return m->secret;
}

void Gatekeeper::setSecret(const QByteArray & secret)
{
	if (m->secret != secret) {
		m->secret = secret;
		emit secretChanged();
	}
}

bool Gatekeeper::authenticate() const
{
	if (secret().isEmpty())
		return true;

	QByteArray hash = Hash(password());

	for (int i = 1; i < m->hashesMin; ++i) {
		hash = Hash(hash);
	}

	for (int i = m->hashesMin; i <= m->hashesMax; ++i) {
		if (hash == secret())
			return true;
		hash = Hash(hash);
	}

	return false;
}

QByteArray Gatekeeper::makeSecret(const QString & password)
{
	QByteArray hash = Hash(password);

	for (int i = 1; i < pickNumberOfHashes(); ++i)
		hash = Hash(hash);

	return hash;
}

QByteArray Gatekeeper::Hash(const QString & string)
{
	return QCryptographicHash::hash(string.toUtf8(), QCryptographicHash::Sha3_512).toHex();
}

int Gatekeeper::pickNumberOfHashes() const
{
	return static_cast<int>(QRandomGenerator::global()->bounded(static_cast<unsigned int>(hashesLow()), static_cast<unsigned int>(hashesHigh()) + 1));
}

}
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

//(c)C: Copyright © 2021-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
