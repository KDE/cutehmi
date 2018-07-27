#ifndef DATABASECONNECTIONDATA_HPP
#define DATABASECONNECTIONDATA_HPP

#include <QString>

namespace cutehmi {
namespace termobot {

struct DatabaseConnectionData
{
    QString type;
    QString connectionName;
    QString hostName;
    int port;
    QString databaseName;
    QString userName;
    QString password;
};

}
}

#endif // DATABASECONNECTIONDATA_HPP

