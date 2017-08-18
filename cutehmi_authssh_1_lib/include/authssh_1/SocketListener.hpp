#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QObject>

class SocketListener : public QObject
{
    Q_OBJECT
public:
    explicit SocketListener(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SOCKETLISTENER_H