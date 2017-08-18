#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH__1_SSHCLIENT_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH__1_SSHCLIENT_HPP

#include <QObject>

class SSHClient : public QObject
{
    Q_OBJECT
public:
    explicit SSHClient(QObject *parent = nullptr);

signals:

public slots:
};

#endif
