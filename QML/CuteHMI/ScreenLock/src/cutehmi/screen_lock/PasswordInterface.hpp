#ifndef PASSWORDINTERFACE_HPP
#define PASSWORDINTERFACE_HPP

#include <QSettings>
#include <QCryptographicHash>
#include <QQmlExtensionPlugin>

namespace cutehmi {
namespace screen_lock {

class PasswordInterface : public QObject
{
    Q_OBJECT
public:
    explicit PasswordInterface(QObject *parent = nullptr);

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

#endif // PASSWORDINTERFACE_HPP
