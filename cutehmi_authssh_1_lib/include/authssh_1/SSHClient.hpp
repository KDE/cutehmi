#ifndef SSHCLIENT_HPP
#define SSHCLIENT_HPP

#include <QObject>

class SSHClient : public QObject
{
    Q_OBJECT
public:
    explicit SSHClient(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SSHCLIENT_HPP