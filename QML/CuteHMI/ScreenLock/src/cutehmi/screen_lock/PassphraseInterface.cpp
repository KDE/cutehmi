#include "PassphraseInterface.hpp"

namespace cutehmi {
namespace screen_lock {

PassphraseInterface::PassphraseInterface(QObject *parent) : QObject(parent), m_crypto(QCryptographicHash::Sha3_512)
{
    m_settings = new QSettings("Termotronika", "CuteHMI", this);
}

bool PassphraseInterface::validatePassphrase(const QString &passphrase)
{
    return passphrase == m_settings->value("screenlockPassphrase", "31415").toString();
}

bool PassphraseInterface::changePassphrase(const QString &oldPassphrase, const QString &newPassphrase)
{
    if (validatePassphrase(oldPassphrase))
    {
        setPassword(newPassphrase);
        return true;
    }
    return false;
}

void PassphraseInterface::setPassword(const QString &passphrase)
{
    m_settings->setValue("screenLockPassphrase", passphrase);
}

}
}
