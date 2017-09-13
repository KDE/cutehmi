#ifndef PASSPHRASEINTERFACE_HPP
#define PASSPHRASEINTERFACE_HPP

#include <QSettings>
#include <QCryptographicHash>
#include <QQmlExtensionPlugin>

namespace cutehmi {
namespace screen_lock {

class PassphraseInterface : public QObject
{
    Q_OBJECT
public:
    explicit PassphraseInterface(QObject *parent = nullptr);

    Q_INVOKABLE bool validatePassphrase(const QString &passphrase);

    Q_INVOKABLE bool changePassphrase(const QString &oldPassphrase, const QString &newPassphrase);

private:

    void setPassword(const QString &passphrase);

    QSettings *m_settings;
    QCryptographicHash m_crypto;

signals:

public slots:
};

}
}

#endif // PASSPHRASEINTERFACE_HPP
