#ifndef LOCKSCREENINTERFACE_HPP
#define LOCKSCREENINTERFACE_HPP

#include <QSettings>
#include <QCryptographicHash>
#include <QQmlExtensionPlugin>

namespace cutehmi {
namespace lockscreen {

class Auth : public QObject
{
    Q_OBJECT
public:
    explicit Auth(QObject *parent = nullptr);

    Q_PROPERTY(bool locked MEMBER m_locked NOTIFY lockedChanged)

    Q_INVOKABLE bool validatePassword(const QString &password);

    Q_INVOKABLE bool changePassword(const QString &oldPassword, const QString &newPassword);

private:

    int getNumberOfHashes();

    void setPassword(const QString &password);

    QSettings *m_settings;

    int m_lowerBoundOfHashes;
    int m_upperBoundOfHashes;

    bool m_locked;

signals:

    void lockedChanged();
};

}
}

#endif // LOCKSCREENINTERFACE_HPP
