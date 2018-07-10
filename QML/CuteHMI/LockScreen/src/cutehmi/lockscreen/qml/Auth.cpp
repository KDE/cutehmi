#include "Auth.hpp"

#include <QDebug>
#include <QDateTime>

namespace cutehmi {
namespace lockscreen {
namespace qml {

Auth::Auth(QObject * parent) : QObject(parent),
    m_lowerBoundOfHashes(9000), m_upperBoundOfHashes(10000), m_locked(false)
{
    m_settings = new QSettings(this);
	m_settings->beginGroup("cutehmi_lockscreen_1");
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
}

bool Auth::checkPassword(const QString & password)
{
    if (validatePassword(password) != true)
        return false;
	QString passwordHash = m_settings->value("password").toString();
	if (passwordHash.isEmpty())
		return true;
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha3_512).toHex();
    for (int i = 0; i < m_upperBoundOfHashes; ++i) {
        if (i >= m_lowerBoundOfHashes && hash == passwordHash)
            return true;
        hash = QCryptographicHash::hash(hash, QCryptographicHash::Sha3_512).toHex();
    }
    return false;
}

bool Auth::validatePassword(const QString & password)
{
    if (password.length() != 0)
        return true;
    return false;
}

bool Auth::changePassword(const QString & newPassword, const QString & oldPassword)
{
    if (checkPassword(oldPassword)) {
        changePassword(newPassword);
        return true;
    }
    return false;
}

void Auth::changePassword(const QString & password)
{
    if (validatePassword(password) != true)
        return;
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha3_512).toHex();
    for (int i = 0; i < getNumberOfHashes(); ++i)
        hash = QCryptographicHash::hash(hash, QCryptographicHash::Sha3_512).toHex();
    QString passwordHash = hash;
	m_settings->setValue("password", passwordHash);
}

int Auth::getNumberOfHashes()
{
    return qrand() % (m_upperBoundOfHashes - m_lowerBoundOfHashes) + m_lowerBoundOfHashes;
}

}
}
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
