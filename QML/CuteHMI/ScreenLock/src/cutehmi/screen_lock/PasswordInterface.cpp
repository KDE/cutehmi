#include "PasswordInterface.hpp"

namespace cutehmi {
namespace screen_lock {

PasswordInterface::PasswordInterface(QObject *parent) : QObject(parent), m_crypto(QCryptographicHash::Sha3_512)
{
    m_settings = new QSettings("Termotronika", "CuteHMI", this);
}

bool PasswordInterface::validatePassword(const QString &password)
{
    return password == m_settings->value("screenlockPassword", "31415").toString();
}

bool PasswordInterface::changePassword(const QString &oldPassword, const QString &newPassword)
{
    if (validatePassword(oldPassword))
    {
        setPassword(newPassword);
        return true;
    }
    return false;
}

void PasswordInterface::setPassword(const QString &password)
{
    m_settings->setValue("screenLockPassword", password);
}

}
}
