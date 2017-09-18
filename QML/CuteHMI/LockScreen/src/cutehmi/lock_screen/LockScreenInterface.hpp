#ifndef LOCKSCREENINTERFACE_HPP
#define LOCKSCREENINTERFACE_HPP

#include <QSettings>
#include <QCryptographicHash>
#include <QQmlExtensionPlugin>

namespace cutehmi {
namespace lock_screen {

class LockScreenInterface : public QObject
{
    Q_OBJECT
public:
    explicit LockScreenInterface(QObject *parent = nullptr);

    Q_INVOKABLE bool validatePassword(const QString &password);

    Q_INVOKABLE bool changePassword(const QString &oldPassword, const QString &newPassword);

private:

    int getNumberOfHashes();

    void setPassword(const QString &password);

    QSettings *m_settings;

    int lowerBoundOfHashes;
    int upperBoundOfHashes;

signals:

public slots:
};

}
}

#endif // LOCKSCREENINTERFACE_HPP
