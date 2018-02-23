#ifndef CUTEHMI_QML_CUTEHMI_LOCKSCREEN_SRC_CUTEHMI_LOCK__SCREEN_AUTH_HPP
#define CUTEHMI_QML_CUTEHMI_LOCKSCREEN_SRC_CUTEHMI_LOCK__SCREEN_AUTH_HPP

#include <QSettings>
#include <QCryptographicHash>
#include <QQmlExtensionPlugin>

namespace cutehmi {
namespace lockscreen {
namespace qml {

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
}

#endif
