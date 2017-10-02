#include "Auth.hpp"

#include <QDebug>
#include <QDateTime>

namespace cutehmi {
namespace lockscreen {

Auth::Auth(QObject * parent) : QObject(parent),
    m_lowerBoundOfHashes(9000), m_upperBoundOfHashes(10000), m_locked(false)
{
    m_settings = new QSettings(this);
    m_settings->beginGroup("LockScreen");
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
}

bool Auth::validatePassword(const QString &password)
{
    QString passwordHash = m_settings->value("lockScreenPassword").toString();
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha3_512).toHex();
    for (int i = 0; i < m_upperBoundOfHashes; ++i) {
        if (i >= m_lowerBoundOfHashes && hash == passwordHash)
            return true;
        hash = QCryptographicHash::hash(hash, QCryptographicHash::Sha3_512).toHex();
    }
    return false;
}

bool Auth::changePassword(const QString &oldPassword, const QString &newPassword)
{
    if (validatePassword(oldPassword))
    {
        setPassword(newPassword);
        return true;
    }
    return false;
}

void Auth::setPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha3_512).toHex();
    for (int i = 0; i < getNumberOfHashes(); ++i)
    {
        hash = QCryptographicHash::hash(hash, QCryptographicHash::Sha3_512).toHex();
    }
    QString passwordHash = hash;
    m_settings->setValue("lockScreenPassword", passwordHash);
}

int Auth::getNumberOfHashes()
{
    return qrand() % (m_upperBoundOfHashes - m_lowerBoundOfHashes) + m_lowerBoundOfHashes;
}

}
}
