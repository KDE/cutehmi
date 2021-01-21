#include <cutehmi/lockscreen/Gatekeeper.hpp>

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
