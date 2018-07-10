#ifndef H_QML_CUTEHMI_LOCKSCREEN_SRC_CUTEHMI_LOCKSCREEN_QML_AUTH_HPP
#define H_QML_CUTEHMI_LOCKSCREEN_SRC_CUTEHMI_LOCKSCREEN_QML_AUTH_HPP

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

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
