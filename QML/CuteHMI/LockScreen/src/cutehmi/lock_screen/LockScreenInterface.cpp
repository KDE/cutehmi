#include "LockScreenInterface.hpp"

#include <QDebug>
#include <QDateTime>

namespace cutehmi {
namespace lock_screen {

LockScreenInterface::LockScreenInterface(QObject *parent) : QObject(parent),
    lowerBoundOfHashes(9000), upperBoundOfHashes(10000)
{
    m_settings = new QSettings("Termotronika", "CuteHMI", this);
    qsrand(QTime::currentTime().msec());
}

bool LockScreenInterface::validatePassword(const QString &password)
{
    QString passwordHash = m_settings->value("lockScreenPassword").toString();
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha3_512).toHex();
    for (int i = 0; i < upperBoundOfHashes; ++i)
    {
        if (i >= lowerBoundOfHashes && hash == passwordHash)
            return true;
        hash = QCryptographicHash::hash(hash, QCryptographicHash::Sha3_512).toHex();
    }
    return false;
}

bool LockScreenInterface::changePassword(const QString &oldPassword, const QString &newPassword)
{
    if (validatePassword(oldPassword))
    {
        setPassword(newPassword);
        return true;
    }
    return false;
}

void LockScreenInterface::setPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha3_512).toHex();
    for (int i = 0; i < getNumberOfHashes(); ++i)
    {
        hash = QCryptographicHash::hash(hash, QCryptographicHash::Sha3_512).toHex();
    }
    QString passwordHash = hash;
    m_settings->setValue("lockScreenPassword", passwordHash);
}

int LockScreenInterface::getNumberOfHashes()
{
    return qrand() % (upperBoundOfHashes - lowerBoundOfHashes) + lowerBoundOfHashes;
}

}
}
