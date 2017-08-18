#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH__1_SOCKETLISTENER_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH__1_SOCKETLISTENER_HPP

#include <QObject>

class SocketListener : public QObject
{
    Q_OBJECT
public:
    explicit SocketListener(QObject *parent = nullptr);

signals:

public slots:
};

#endif
