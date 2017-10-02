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
    explicit Auth(QObject * parent = nullptr);

    Q_PROPERTY(bool locked MEMBER m_locked NOTIFY lockedChanged)     ///< @todo implement.

    Q_INVOKABLE bool checkPassword(const QString & password);

    Q_INVOKABLE bool validatePassword(const QString & password);

    Q_INVOKABLE bool changePassword(const QString & newPassword, const QString & oldPassword);

    Q_INVOKABLE void changePassword(const QString & password);

private:

    int getNumberOfHashes();

    QSettings * m_settings;

    int m_lowerBoundOfHashes;
    int m_upperBoundOfHashes;

    bool m_locked;  ///< @todo implement.

signals:

    void lockedChanged();
};

}
}

#endif // LOCKSCREENINTERFACE_HPP
